#include "ast.h"

#include <ctype.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast_node_array.h"
#include "token_array.h"
#include "utils.h"

int token_index;

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
    printf(#t "\n");  \
    break;            \
  }

#define PRINT_TOKEN_TYPE(t)   \
  if (ast->token.type == t) { \
    printf(#t "\n");          \
  }

#define NODE_UNARY_OP(t)                                             \
  if (current_token.type == t) {                                     \
    if (stack->size) {                                               \
      node.left = make_node(pop_ast_node_array(stack));              \
    } else {                                                         \
      throw_error_tudor(                                             \
          "incorrect operator stack at ast build, expecting 1 arg"); \
    }                                                                \
  }

#define NODE_BINARY_OP(t)                                             \
  if (current_token.type == t) {                                      \
    if (stack->size > 1) {                                            \
      node.right = make_node(pop_ast_node_array(stack));              \
      node.left = make_node(pop_ast_node_array(stack));               \
    } else {                                                          \
      throw_error_tudor(                                              \
          "incorrect operator stack at ast build, expecting 2 args"); \
    }                                                                 \
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
  return token.type == TOKEN_NUMBER || token.type == TOKEN_X;
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

bool isFunctionChar(char c) { return isalpha(c) && c != 'x' && c != 'X'; }

token_t next(char* data) {
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

    throw_error_tudor("unknown function: '%s'", str);
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

  throw_error_tudor("unknown char: '%c'", current_char);

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
      printf("TOKEN_NUMBER: %lf\n", token.val);
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

    default: {
      printf("Unknown token\n");
      break;
    }
  }
}

void print_tokens(token_array_t* token_array) {
  printf("\nNum tokens: %d\n", token_array->size);

  for (int i = 0; i < token_array->size; i++) {
    print_token(token_array->tokens[i]);
  }
}

void print_ast(node_t* ast, int indentation = 0, bool left = false) {
  if (ast) {
    for (int i = 0; i < indentation; i++) {
      printf("  ");
    }

    printf("%c ", left ? 'L' : 'R');

    if (ast->token.type == TOKEN_NUMBER) {
      printf("%lf\n", ast->token.val);
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
          throw_error_tudor("incorrect right paranthesis");
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
      throw_error_tudor("incorrect left paranthesis");
    }

    push_token_array(postfix_token_array, token);
  }

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
    throw_error_tudor(
        "incorrect final ast stack size ... expecting 1 but got %d",
        stack->size);

    return nullptr;
  }

  return make_node(pop_ast_node_array(stack));
}

node_t* parse_ast_from_string_tudor(char* data) {
  token_array_t* tokens = tokenize(data);
  token_array_t* postfix_tokens = convert_token_array_to_postfix(tokens);

  printf("\nTOKENS: ");
  print_tokens(tokens);

  destory_token_array(tokens);

  printf("\nPOSTFIX: ");
  print_tokens(postfix_tokens);

  node_t* ast = build_ast_from_token_array(postfix_tokens);
  destory_token_array(postfix_tokens);

  printf("\nAST: \n");
  print_ast(ast);

  return ast;
}