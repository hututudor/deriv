#include "token_array.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

token_array_t* init_token_array() {
  token_array_t* array = (token_array_t*)malloc(sizeof(token_array_t));
  array->tokens = (token_t**)malloc(sizeof(token_t*) * 1000);
  array->size = 0;

  return array;
}

void destory_token_array(token_array_t* array) {
  while (array->size) {
    pop_token_array(array);
  }

  free(array);
}

void push_token_array(token_array_t* array, token_t* token) {
  array->tokens[array->size++] = token;
}

token_t* top_token_array(token_array_t* array) {
  if (array->size) {
    return array->tokens[array->size - 1];
  }

  return nullptr;
}

token_t pop_token_array(token_array_t* array) {
  token_t* top_token = top_token_array(array);

  if (!top_token) {
    throw_error_tudor("trying to pop an empty stack");
  }

  token_t token = {.type = top_token->type, .val = top_token->val};

  // this might leak memory ??? TODO(tudor): investigate further
  array->size--;

  return token;
}
