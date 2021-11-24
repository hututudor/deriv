#include "ast.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int token_index;

#define MAKE_TOKEN(t) \
  token->type = t;    \
  token_index++;      \
  return token;

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
    int num = 0;

    while (isdigit(current_char)) {
      num *= 10;
      num += current_char - '0';
      token_index++;
      current_char = data[token_index];
    }

    token->type = TOKEN_NUMBER;
    token->val = num;

    return token;
  }

  if (current_char == '+') {
    MAKE_TOKEN(TOKEN_PLUS);
  }

  if (current_char == '-') {
    MAKE_TOKEN(TOKEN_PLUS);
  }

  if (current_char == '*') {
    MAKE_TOKEN(TOKEN_PLUS);
  }

  if (current_char == '/') {
    MAKE_TOKEN(TOKEN_DIV);
  }

  throw_error_tudor("unknown char: '%c'", current_char);

  free(token);
  return nullptr;
}

token_t* seek(char* data) {
  int current_index = token_index;
  token_t* token = next(data);
  token_index = current_index;

  return token;
}

token_array_t tokenize(char* data) {
  token_array_t token_array;

  token_array.first = nullptr;
  token_array.size = 0;

  token_index = 0;

  token_t* current_token = nullptr;

  do {
    current_token = next(data);

    if (current_token) {
      token_array.first[token_array.size++];
    }
  } while (current_token);

  return token_array;
}

void print_tokens(token_array_t token_array) {
  printf("Num tokens: %d\n", token_array.size);
}

ast_t* parse_ast_from_string_tudor(char* data) {
  token_array_t token_array = tokenize(data);
  print_tokens(token_array);

  return nullptr;
}