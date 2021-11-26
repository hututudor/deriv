#include "ast.h"

#include <ctype.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_array.h"
#include "utils.h"

int token_index;

#define MAKE_TOKEN(t, c)   \
  if (current_char == c) { \
    token->type = t;       \
    token_index++;         \
    return token;          \
  }

#define MAKE_FUNCTION_TOKEN(t, c) \
  if (strcasecmp(str, c) == 0) {  \
    free(str);                    \
    token->type = t;              \
    return token;                 \
  }

#define PARSE_CASE(t) \
  case t: {           \
    printf(#t "\n");  \
    break;            \
  }

bool isOperand(token_t* token) {
  return token->type == TOKEN_PLUS || token->type == TOKEN_MINUS ||
         token->type == TOKEN_MUL || token->type == TOKEN_DIV ||
         token->type == TOKEN_POW || token->type == TOKEN_SQRT ||
         token->type == TOKEN_SIN || token->type == TOKEN_COS ||
         token->type == TOKEN_TAN || token->type == TOKEN_COTAN ||
         token->type == TOKEN_ARCSIN || token->type == TOKEN_ARCCOS ||
         token->type == TOKEN_ARCTAN || token->type == TOKEN_ARCCOTAN ||
         token->type == TOKEN_LG || token->type == TOKEN_LN;
}

bool isFunc(token_t* token) {
  return token->type == TOKEN_SQRT || token->type == TOKEN_SIN ||
         token->type == TOKEN_COS || token->type == TOKEN_TAN ||
         token->type == TOKEN_COTAN || token->type == TOKEN_ARCSIN ||
         token->type == TOKEN_ARCCOS || token->type == TOKEN_ARCTAN ||
         token->type == TOKEN_ARCCOTAN || token->type == TOKEN_LG ||
         token->type == TOKEN_LN;
}

int getOperandPrecedence(token_t* token) {
  if (token->type == TOKEN_POW) {
    return 4;
  }

  if (token->type == TOKEN_MUL || token->type == TOKEN_DIV) {
    return 3;
  }

  if (token->type == TOKEN_PLUS || token->type == TOKEN_MINUS) {
    return 2;
  }

  return 1;
}

bool isRightAssociative(token_t* token) {
  return token->type == TOKEN_POW || isFunc(token);
}

token_t* next(char* data) {
  while (data[token_index] == ' ' || data[token_index] == '\t' ||
         data[token_index] == '\n') {
    token_index++;
  }

  char current_char = data[token_index];

  if (current_char == 0) {
    return nullptr;
  }

  token_t* token = (token_t*)malloc(sizeof(token_t));

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

    token->type = TOKEN_NUMBER;
    token->val = num;

    return token;
  }

  if (isalpha(current_char)) {
    int index = 0;
    char* str = (char*)malloc(1000);
    memset(str, 0, 1000);

    while (isalpha(current_char)) {
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

    MAKE_FUNCTION_TOKEN(TOKEN_X, "x");

    throw_error_tudor("unknown function: '%s'", str);

    free(str);
    return nullptr;
  }

  MAKE_TOKEN(TOKEN_PLUS, '+');
  MAKE_TOKEN(TOKEN_MINUS, '-');
  MAKE_TOKEN(TOKEN_MUL, '*');
  MAKE_TOKEN(TOKEN_DIV, '/');
  MAKE_TOKEN(TOKEN_L_PAREN, '(');
  MAKE_TOKEN(TOKEN_R_PAREN, ')');
  MAKE_TOKEN(TOKEN_POW, '^');

  throw_error_tudor("unknown char: '%c'", current_char);

  free(token);
  return nullptr;
}

token_array_t* tokenize(char* data) {
  token_array_t* token_array = init_token_array();

  token_index = 0;

  token_t* current_token = nullptr;

  do {
    current_token = next(data);

    if (current_token) {
      push_token_array(token_array, current_token);
    }
  } while (current_token);

  return token_array;
}

void print_tokens(token_array_t* token_array) {
  printf("\nNum tokens: %d\n", token_array->size);

  for (int i = 0; i < token_array->size; i++) {
    switch (token_array->tokens[i]->type) {
      case TOKEN_NUMBER: {
        printf("TOKEN_NUMBER: %lf\n", token_array->tokens[i]->val);
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
}

token_array_t* convert_token_array_to_postfix(token_array_t* token_array) {
  token_array_t* postfix_token_array = init_token_array();
  token_array_t* stack = init_token_array();

  for (int i = 0; i < token_array->size; i++) {
    token_t* current_token = token_array->tokens[i];

    if (current_token->type == TOKEN_NUMBER || current_token->type == TOKEN_X) {
      push_token_array(postfix_token_array, current_token);
      continue;
    }

    if (current_token->type == TOKEN_L_PAREN) {
      push_token_array(stack, current_token);
      continue;
    }

    if (current_token->type == TOKEN_R_PAREN) {
      token_t current_token;

      do {
        if (stack->size == 0) {
          throw_error_tudor("incorrect right paranthesis");
        }

        current_token = pop_token_array(stack);

        if (current_token.type != TOKEN_L_PAREN) {
          token_t* new_token = (token_t*)malloc(sizeof(token_t));

          new_token->type = current_token.type;
          new_token->val = 0;

          push_token_array(postfix_token_array, new_token);
        }

      } while (current_token.type != TOKEN_L_PAREN);

      continue;
    }

    if (isOperand(current_token)) {
      token_t* top = top_token_array(stack);

      if (stack->size == 0 || top->type == TOKEN_L_PAREN) {
        push_token_array(stack, current_token);
        continue;
      }

      if (getOperandPrecedence(current_token) > getOperandPrecedence(top) ||
          (getOperandPrecedence(current_token) == getOperandPrecedence(top) &&
           isRightAssociative(current_token))) {
        push_token_array(stack, current_token);
        continue;
      }

      while (
          stack->size &&
              getOperandPrecedence(current_token) < getOperandPrecedence(top) ||
          (getOperandPrecedence(current_token) == getOperandPrecedence(top) &&
           !isRightAssociative(current_token))) {
        push_token_array(postfix_token_array, top);

        token_t* token = top_token_array(stack);

        top = (token_t*)malloc(sizeof(token_t));
        top->type = token->type;
        top->val = token->val;

        pop_token_array(stack);
      }

      push_token_array(stack, current_token);

      continue;
    }
  }

  while (stack->size) {
    token_t token = pop_token_array(stack);

    if (token.type == TOKEN_L_PAREN) {
      throw_error_tudor("incorrect left paranthesis");
    }

    token_t* tk = (token_t*)malloc(sizeof(token_t));
    tk->type = token.type;
    tk->val = token.val;

    push_token_array(postfix_token_array, tk);
  }

  return postfix_token_array;
}

ast_t* parse_ast_from_string_tudor(char* data) {
  token_array_t* tokens = tokenize(data);
  token_array_t* postfix_tokens = convert_token_array_to_postfix(tokens);

  printf("\nTOKENS: ");
  print_tokens(tokens);

  printf("\nPOSTFIX: ");
  print_tokens(postfix_tokens);

  return nullptr;
}