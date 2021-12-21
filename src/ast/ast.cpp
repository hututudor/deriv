#include "ast.h"

#include <ctype.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "../utils/ast_node_array.h"
#include "../utils/string.h"
#include "../utils/token_array.h"
#include "../utils/utils.h"

int token_index = 0;

#define MAKE_TOKEN(t, c)   \
  if (current_char == c) { \
    token.type = t;        \
    token_index++;         \
    return token;          \
  }

#define MAKE_FUNCTION_TOKEN(t, c) \
  if (strcasecmp(str, c) == 0) {  \
    free(str);                    \
    token.type = t;               \
    return token;                 \
  }

#define PARSE_CASE(t) \
  case t: {           \
    log(#t "\n");     \
    break;            \
  }

#define PRINT_TOKEN_TYPE(t)   \
  if (ast->token.type == t) { \
    log(#t "\n");             \
  }

#define NODE_UNARY_OP(t)                                                     \
  if (current_token.type == t) {                                             \
    if (stack->size) {                                                       \
      node.left = make_node(pop_ast_node_array(stack));                      \
    } else {                                                                 \
      throw_error("incorrect operator stack at ast build, expecting 1 arg"); \
    }                                                                        \
  }

#define NODE_BINARY_OP(t)                                                     \
  if (current_token.type == t) {                                              \
    if (stack->size > 1) {                                                    \
      node.right = make_node(pop_ast_node_array(stack));                      \
      node.left = make_node(pop_ast_node_array(stack));                       \
    } else {                                                                  \
      throw_error("incorrect operator stack at ast build, expecting 2 args"); \
    }                                                                         \
  }

#define TOKEN_STRING_CONVERT(t, c)  \
  if (current_token.type == t) {    \
    concat_const_string(string, c); \
    continue;                       \
  }

bool isFunc(token_t token) {
  return token.type == TOKEN_SQRT || token.type == TOKEN_SIN ||
         token.type == TOKEN_COS || token.type == TOKEN_TAN ||
         token.type == TOKEN_COTAN || token.type == TOKEN_ARCSIN ||
         token.type == TOKEN_ARCCOS || token.type == TOKEN_ARCTAN ||
         token.type == TOKEN_ARCCOTAN || token.type == TOKEN_LG ||
         token.type == TOKEN_LN;
}

bool isOperator(token_t token) {
  return token.type == TOKEN_PLUS || token.type == TOKEN_MINUS ||
         token.type == TOKEN_MUL || token.type == TOKEN_DIV ||
         token.type == TOKEN_POW || isFunc(token);
}

bool isOperand(token_t token) {
  return token.type == TOKEN_NUMBER || token.type == TOKEN_X ||
         token.type == TOKEN_E;
}

int getOperatorPrecedence(token_t token) {
  if (isFunc(token)) {
    return 5;
  }

  if (token.type == TOKEN_POW) {
    return 4;
  }

  if (token.type == TOKEN_MUL || token.type == TOKEN_DIV) {
    return 3;
  }

  if (token.type == TOKEN_PLUS || token.type == TOKEN_MINUS) {
    return 2;
  }

  return 1;
}

bool isRightAssociative(token_t token) { return token.type == TOKEN_POW; }

bool isFunctionChar(char c) {
  return isalpha(c) && strchr("xXeE", c) == nullptr;
}

token_t next(char* data) {
  if (!data) {
    throw_error("unreachable");
  }

  while (data[token_index] == ' ' || data[token_index] == '\t' ||
         data[token_index] == '\n') {
    token_index++;
  }

  char current_char = data[token_index];

  token_t token;

  if (current_char == 0) {
    token.type = TOKEN_EOF;

    return token;
  }

  if (isdigit(current_char)) {
    double num = 0;

    while (isdigit(current_char)) {
      num *= 10;
      num += current_char - '0';
      token_index++;
      current_char = data[token_index];
    }

    if (current_char == '.') {
      double exp = 0;
      int exp_size = 0;

      token_index++;
      current_char = data[token_index];

      while (isdigit(current_char)) {
        exp_size++;
        exp *= 10;
        exp += current_char - '0';
        token_index++;
        current_char = data[token_index];
      }

      if (exp_size) {
        exp /= pow(10, exp_size);
        num += exp;
      }
    }

    token.type = TOKEN_NUMBER;
    token.val = num;

    return token;
  }

  if (isFunctionChar(current_char)) {
    int index = 0;
    char* str = (char*)malloc(1000);
    memset(str, 0, 1000);

    while (isFunctionChar(current_char)) {
      str[index++] = current_char;
      token_index++;
      current_char = data[token_index];
    }

    MAKE_FUNCTION_TOKEN(TOKEN_SQRT, "sqrt");
    MAKE_FUNCTION_TOKEN(TOKEN_SIN, "sin");
    MAKE_FUNCTION_TOKEN(TOKEN_COS, "cos");
    MAKE_FUNCTION_TOKEN(TOKEN_TAN, "tan");
    MAKE_FUNCTION_TOKEN(TOKEN_TAN, "tg");
    MAKE_FUNCTION_TOKEN(TOKEN_COTAN, "cotan");
    MAKE_FUNCTION_TOKEN(TOKEN_COTAN, "ctg");
    MAKE_FUNCTION_TOKEN(TOKEN_ARCSIN, "arcsin");
    MAKE_FUNCTION_TOKEN(TOKEN_ARCCOS, "arccos");
    MAKE_FUNCTION_TOKEN(TOKEN_ARCTAN, "arctan");
    MAKE_FUNCTION_TOKEN(TOKEN_ARCTAN, "arctg");
    MAKE_FUNCTION_TOKEN(TOKEN_ARCCOTAN, "arccotan");
    MAKE_FUNCTION_TOKEN(TOKEN_ARCCOTAN, "arcctg");
    MAKE_FUNCTION_TOKEN(TOKEN_LG, "lg");
    MAKE_FUNCTION_TOKEN(TOKEN_LN, "ln");

    throw_error("unknown function: '%s'", str);
  }

  MAKE_TOKEN(TOKEN_PLUS, '+');
  MAKE_TOKEN(TOKEN_MINUS, '-');
  MAKE_TOKEN(TOKEN_MUL, '*');
  MAKE_TOKEN(TOKEN_DIV, '/');
  MAKE_TOKEN(TOKEN_L_PAREN, '(');
  MAKE_TOKEN(TOKEN_R_PAREN, ')');
  MAKE_TOKEN(TOKEN_POW, '^');

  MAKE_TOKEN(TOKEN_X, 'x');
  MAKE_TOKEN(TOKEN_X, 'X');
  MAKE_TOKEN(TOKEN_E, 'e');
  MAKE_TOKEN(TOKEN_E, 'E');

  throw_error("unknown char: '%c'", current_char);

  token.type = TOKEN_EOF;
  return token;
}

token_array_t* tokenize(char* data) {
  token_array_t* token_array = init_token_array();

  token_index = 0;

  token_t current_token;

  do {
    current_token = next(data);

    if (current_token.type != TOKEN_EOF) {
      push_token_array(token_array, current_token);
    }
  } while (current_token.type != TOKEN_EOF);

  return token_array;
}

void print_token(token_t token) {
  switch (token.type) {
    case TOKEN_NUMBER: {
      log("TOKEN_NUMBER: %lf\n", token.val);
      break;
    }

      PARSE_CASE(TOKEN_PLUS);
      PARSE_CASE(TOKEN_MINUS);
      PARSE_CASE(TOKEN_MUL);
      PARSE_CASE(TOKEN_DIV);
      PARSE_CASE(TOKEN_L_PAREN);
      PARSE_CASE(TOKEN_R_PAREN);
      PARSE_CASE(TOKEN_POW);
      PARSE_CASE(TOKEN_SQRT);
      PARSE_CASE(TOKEN_SIN);
      PARSE_CASE(TOKEN_COS);
      PARSE_CASE(TOKEN_TAN);
      PARSE_CASE(TOKEN_COTAN);
      PARSE_CASE(TOKEN_ARCSIN);
      PARSE_CASE(TOKEN_ARCCOS);
      PARSE_CASE(TOKEN_ARCTAN);
      PARSE_CASE(TOKEN_ARCCOTAN);
      PARSE_CASE(TOKEN_LG);
      PARSE_CASE(TOKEN_LN);
      PARSE_CASE(TOKEN_X);
      PARSE_CASE(TOKEN_E);

    default: {
      log("Unknown token\n");
      break;
    }
  }
}

void print_tokens(token_array_t* token_array) {
  log("\nNum tokens: %d\n", token_array->size);

  for (int i = 0; i < token_array->size; i++) {
    print_token(token_array->tokens[i]);
  }
}

void print_ast(node_t* ast, int indentation = 0, bool left = false) {
  if (ast) {
    for (int i = 0; i < indentation; i++) {
      log("  ");
    }

    log("%c ", left ? 'L' : 'R');

    if (ast->token.type == TOKEN_NUMBER) {
      log("%lf\n", ast->token.val);
    } else {
      PRINT_TOKEN_TYPE(TOKEN_PLUS);
      PRINT_TOKEN_TYPE(TOKEN_MINUS);
      PRINT_TOKEN_TYPE(TOKEN_MUL);
      PRINT_TOKEN_TYPE(TOKEN_DIV);
      PRINT_TOKEN_TYPE(TOKEN_L_PAREN);
      PRINT_TOKEN_TYPE(TOKEN_R_PAREN);
      PRINT_TOKEN_TYPE(TOKEN_POW);
      PRINT_TOKEN_TYPE(TOKEN_SQRT);
      PRINT_TOKEN_TYPE(TOKEN_SIN);
      PRINT_TOKEN_TYPE(TOKEN_COS);
      PRINT_TOKEN_TYPE(TOKEN_TAN);
      PRINT_TOKEN_TYPE(TOKEN_COTAN);
      PRINT_TOKEN_TYPE(TOKEN_ARCSIN);
      PRINT_TOKEN_TYPE(TOKEN_ARCCOS);
      PRINT_TOKEN_TYPE(TOKEN_ARCTAN);
      PRINT_TOKEN_TYPE(TOKEN_ARCCOTAN);
      PRINT_TOKEN_TYPE(TOKEN_LG);
      PRINT_TOKEN_TYPE(TOKEN_LN);
      PRINT_TOKEN_TYPE(TOKEN_X);
      PRINT_TOKEN_TYPE(TOKEN_E);
    }

    print_ast(ast->left, indentation + 1, true);
    print_ast(ast->right, indentation + 1, false);
  }
}

token_array_t* convert_token_array_to_postfix(token_array_t* token_array) {
  token_array_t* postfix_token_array = init_token_array();
  token_array_t* stack = init_token_array();

  for (int i = 0; i < token_array->size; i++) {
    token_t current_token = token_array->tokens[i];

    if (isOperand(current_token)) {
      push_token_array(postfix_token_array, current_token);
      continue;
    }

    if (current_token.type == TOKEN_L_PAREN) {
      push_token_array(stack, current_token);
      continue;
    }

    if (current_token.type == TOKEN_R_PAREN) {
      token_t tok;

      do {
        if (stack->size == 0) {
          throw_error("incorrect right paranthesis");
        }

        tok = pop_token_array(stack);

        if (tok.type != TOKEN_L_PAREN) {
          push_token_array(postfix_token_array, tok);
        }

      } while (tok.type != TOKEN_L_PAREN);

      continue;
    }

    if (isOperator(current_token)) {
      if (stack->size == 0) {
        push_token_array(stack, current_token);
        continue;
      }

      token_t top = top_token_array(stack);

      if (top.type == TOKEN_L_PAREN) {
        push_token_array(stack, current_token);
        continue;
      }

      if (getOperatorPrecedence(current_token) > getOperatorPrecedence(top) ||
          (getOperatorPrecedence(current_token) == getOperatorPrecedence(top) &&
           isRightAssociative(current_token))) {
        push_token_array(stack, current_token);
        continue;
      }

      do {
        if (!((getOperatorPrecedence(current_token) <
               getOperatorPrecedence(top)) ||
              (getOperatorPrecedence(current_token) ==
                   getOperatorPrecedence(top) &&
               !isRightAssociative(current_token)))) {
          break;
        }

        pop_token_array(stack);
        push_token_array(postfix_token_array, top);

        if (!stack->size) {
          break;
        }

        top = top_token_array(stack);
      } while (stack->size);

      push_token_array(stack, current_token);
    }
  }

  while (stack->size) {
    token_t token = pop_token_array(stack);

    if (token.type == TOKEN_L_PAREN) {
      throw_error("incorrect left paranthesis");
    }

    push_token_array(postfix_token_array, token);
  }

  destory_token_array(stack);
  return postfix_token_array;
}

node_t* build_ast_from_token_array(token_array_t* token_array) {
  ast_node_array_t* nodes = init_ast_node_array();
  ast_node_array_t* stack = init_ast_node_array();

  for (int i = 0; i < token_array->size; i++) {
    token_t current_token = token_array->tokens[i];

    node_t node;
    node.token = current_token;
    node.left = nullptr;
    node.right = nullptr;

    NODE_BINARY_OP(TOKEN_PLUS);
    NODE_BINARY_OP(TOKEN_MINUS);
    NODE_BINARY_OP(TOKEN_MUL);
    NODE_BINARY_OP(TOKEN_DIV);
    NODE_BINARY_OP(TOKEN_POW);

    NODE_UNARY_OP(TOKEN_SQRT);
    NODE_UNARY_OP(TOKEN_SIN);
    NODE_UNARY_OP(TOKEN_COS);
    NODE_UNARY_OP(TOKEN_TAN);
    NODE_UNARY_OP(TOKEN_COTAN);
    NODE_UNARY_OP(TOKEN_ARCSIN);
    NODE_UNARY_OP(TOKEN_ARCCOS);
    NODE_UNARY_OP(TOKEN_ARCTAN);
    NODE_UNARY_OP(TOKEN_ARCCOTAN);
    NODE_UNARY_OP(TOKEN_LG);
    NODE_UNARY_OP(TOKEN_LN);

    push_ast_node_array(stack, node);
  }

  if (stack->size != 1) {
    throw_error("incorrect final ast stack size ... expecting 1 but got %d",
                stack->size);

    return nullptr;
  }

  node_t* final_node = make_node(pop_ast_node_array(stack));

  destory_ast_node_array(nodes);
  destory_ast_node_array(stack);

  return final_node;
}

void dfs_ast_to_token_array(node_t* ast, token_array_t* token_array) {
  if (ast) {
    if (ast->left && !ast->right) {
      push_token_array(token_array, ast->token);

      if (isOperator(ast->token) && ast->left && isOperator(ast->left->token) &&
          (getOperatorPrecedence(ast->token) >
           getOperatorPrecedence(ast->left->token))) {
        push_token_array(token_array, {.type = TOKEN_L_PAREN});
        dfs_ast_to_token_array(ast->left, token_array);
        push_token_array(token_array, {.type = TOKEN_R_PAREN});
      } else {
        dfs_ast_to_token_array(ast->left, token_array);
      }

      return;
    }

    if (isOperator(ast->token) && ast->left && isOperator(ast->left->token) &&
        (getOperatorPrecedence(ast->token) >
         getOperatorPrecedence(ast->left->token))) {
      push_token_array(token_array, {.type = TOKEN_L_PAREN});
      dfs_ast_to_token_array(ast->left, token_array);
      push_token_array(token_array, {.type = TOKEN_R_PAREN});
    } else {
      dfs_ast_to_token_array(ast->left, token_array);
    }

    push_token_array(token_array, ast->token);

    if (isOperator(ast->token) && ast->right && isOperator(ast->right->token) &&
        (getOperatorPrecedence(ast->token) >
             getOperatorPrecedence(ast->right->token) ||
         (getOperatorPrecedence(ast->token) ==
              getOperatorPrecedence(ast->right->token) &&
          (ast->token.type == TOKEN_DIV ||
           ast->token.type != ast->right->token.type) &&
          !isRightAssociative(ast->token)))) {
      push_token_array(token_array, {.type = TOKEN_L_PAREN});
      dfs_ast_to_token_array(ast->right, token_array);
      push_token_array(token_array, {.type = TOKEN_R_PAREN});
    } else {
      dfs_ast_to_token_array(ast->right, token_array);
    }
  }
}

token_array_t* ast_to_token_array(node_t* ast) {
  token_array_t* tokens = init_token_array();

  dfs_ast_to_token_array(ast, tokens);

  return tokens;
}

string_t* token_array_to_string(token_array_t* token_array) {
  string_t* string = init_string();

  for (int i = 0; i < token_array->size; i++) {
    token_t current_token = token_array->tokens[i];

    if (current_token.type == TOKEN_NUMBER) {
      char* buffer = (char*)malloc(100);

      sprintf(buffer, "%g", current_token.val);
      concat_string(string, buffer);

      free(buffer);

      continue;
    }

    TOKEN_STRING_CONVERT(TOKEN_PLUS, " + ");
    TOKEN_STRING_CONVERT(TOKEN_MINUS, " - ");
    TOKEN_STRING_CONVERT(TOKEN_MUL, " * ");
    TOKEN_STRING_CONVERT(TOKEN_DIV, " / ");
    TOKEN_STRING_CONVERT(TOKEN_L_PAREN, "(");
    TOKEN_STRING_CONVERT(TOKEN_R_PAREN, ")");
    TOKEN_STRING_CONVERT(TOKEN_POW, " ^ ");
    TOKEN_STRING_CONVERT(TOKEN_SQRT, "sqrt");
    TOKEN_STRING_CONVERT(TOKEN_SIN, "sin");
    TOKEN_STRING_CONVERT(TOKEN_COS, "cos");
    TOKEN_STRING_CONVERT(TOKEN_TAN, "tan");
    TOKEN_STRING_CONVERT(TOKEN_COTAN, "cotan");
    TOKEN_STRING_CONVERT(TOKEN_ARCSIN, "arcsin");
    TOKEN_STRING_CONVERT(TOKEN_ARCCOS, "arccos");
    TOKEN_STRING_CONVERT(TOKEN_ARCTAN, "arctan");
    TOKEN_STRING_CONVERT(TOKEN_ARCCOTAN, "arccotan");
    TOKEN_STRING_CONVERT(TOKEN_LG, "lg");
    TOKEN_STRING_CONVERT(TOKEN_LN, "ln");
    TOKEN_STRING_CONVERT(TOKEN_X, "x");
    TOKEN_STRING_CONVERT(TOKEN_E, "e");
  }

  return string;
}

token_array_t* hydrate_infix_token_array(token_array_t* token_array) {
  token_array_t* hydrated_token_array_pase_1 = init_token_array();
  token_array_t* hydrated_token_array_pase_2 = init_token_array();
  token_array_t* hydrated_token_array_pase_3 = init_token_array();

  for (int i = 0; i < token_array->size; i++) {
    token_t current_token = token_array->tokens[i];

    if (isFunc(current_token) && i < (token_array->size - 1) &&
        token_array->tokens[i + 1].type != TOKEN_L_PAREN) {
      push_token_array(hydrated_token_array_pase_1, current_token);

      token_t token_l_parens;
      token_l_parens.type = TOKEN_L_PAREN;
      token_l_parens.val = 0;

      token_t token_r_parens;
      token_r_parens.type = TOKEN_R_PAREN;
      token_r_parens.val = 0;

      push_token_array(hydrated_token_array_pase_1, token_l_parens);
      while (i < (token_array->size - 1) &&
             !isOperator(token_array->tokens[i + 1])) {
        push_token_array(hydrated_token_array_pase_1,
                         token_array->tokens[i + 1]);
        i++;
      }
      push_token_array(hydrated_token_array_pase_1, token_r_parens);

      continue;
    }

    push_token_array(hydrated_token_array_pase_1, current_token);
  }

  for (int i = 0; i < hydrated_token_array_pase_1->size; i++) {
    token_t current_token = hydrated_token_array_pase_1->tokens[i];

    token_t token_0;
    token_0.type = TOKEN_NUMBER;
    token_0.val = 0;

    if (current_token.type == TOKEN_MINUS) {
      if (hydrated_token_array_pase_2->size == 0) {
        push_token_array(hydrated_token_array_pase_2, token_0);
      } else {
        token_t top = top_token_array(hydrated_token_array_pase_2);

        if (!isOperand(top) && top.type != TOKEN_R_PAREN) {
          if (top.type == TOKEN_L_PAREN) {
            push_token_array(hydrated_token_array_pase_2, token_0);
          }

          if (top.type == TOKEN_PLUS) {
            pop_token_array(hydrated_token_array_pase_2);
          }

          if (top.type == TOKEN_MUL || top.type == TOKEN_DIV ||
              top.type == TOKEN_POW) {
            throw_error("missing paranthesis surrounding negative value");
          }
        }
      }
    }

    if (current_token.type == TOKEN_PLUS) {
      if (hydrated_token_array_pase_2->size == 0) {
        push_token_array(hydrated_token_array_pase_2, token_0);
      } else {
        token_t top = top_token_array(hydrated_token_array_pase_2);

        if (!isOperand(top) && top.type != TOKEN_R_PAREN) {
          if (top.type == TOKEN_L_PAREN) {
            push_token_array(hydrated_token_array_pase_2, token_0);
          }

          if (top.type == TOKEN_MINUS) {
            continue;
          }

          if (top.type == TOKEN_MUL || top.type == TOKEN_DIV ||
              top.type == TOKEN_POW) {
            throw_error("missing paranthesis surrounding negative value");
          }
        }
      }
    }

    push_token_array(hydrated_token_array_pase_2, current_token);
  }

  for (int i = 0; i < hydrated_token_array_pase_2->size; i++) {
    token_t current_token = hydrated_token_array_pase_2->tokens[i];

    if (isFunc(current_token) || current_token.type == TOKEN_X ||
        current_token.type == TOKEN_E || current_token.type == TOKEN_L_PAREN) {
      if (hydrated_token_array_pase_3->size) {
        token_t top = top_token_array(hydrated_token_array_pase_3);

        if (isOperand(top) || top.type == TOKEN_R_PAREN) {
          token_t token;
          token.type = TOKEN_MUL;
          token.val = 0;

          push_token_array(hydrated_token_array_pase_3, token);
        }
      }
    }

    push_token_array(hydrated_token_array_pase_3, current_token);
  }

  destory_token_array(hydrated_token_array_pase_1);
  destory_token_array(hydrated_token_array_pase_2);
  return hydrated_token_array_pase_3;
}

node_t* parse_ast_from_string(char* data) {
  token_array_t* tokens = tokenize(data);

  log("\nTOKENS: ");
  print_tokens(tokens);

  token_array_t* hydrated_tokens = hydrate_infix_token_array(tokens);
  destory_token_array(tokens);

  log("\nHYDRATED TOKENS: ");
  print_tokens(hydrated_tokens);

  token_array_t* postfix_tokens =
      convert_token_array_to_postfix(hydrated_tokens);
  destory_token_array(hydrated_tokens);

  log("\nPOSTFIX: ");
  print_tokens(postfix_tokens);

  node_t* ast = build_ast_from_token_array(postfix_tokens);
  destory_token_array(postfix_tokens);

  log("\nAST: \n");
  print_ast(ast);

  return ast;
}

char* convert_ast_to_expression(node_t* ast) {
  token_array_t* tokens = ast_to_token_array(ast);

  log("\nCONVERTED TOKENS:");
  print_tokens(tokens);

  string_t* string = token_array_to_string(tokens);
  destory_token_array(tokens);

  char* expression = get_c_string(string);
  destory_string(string);

  log("\nEXPRESSION:\n");
  log("%s\n", expression);

  return expression;
}

void destroy_ast(node_t* ast) {
  if (ast) {
    destroy_ast(ast->left);
    destroy_ast(ast->right);

    free(ast);
  }
}

node_t* clone_ast(node_t* ast) {
  if (!ast) return nullptr;

  node_t* node = (node_t*)malloc(sizeof(node_t));
  node->token = ast->token;

  node->left = clone_ast(ast->left);
  node->right = clone_ast(ast->right);

  return node;
}