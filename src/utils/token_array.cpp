#include "token_array.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define TOKEN_ARRAY_ALLOC_SIZE 1000

token_array_t* init_token_array() {
  token_array_t* array = (token_array_t*)malloc(sizeof(token_array_t));

  array->tokens = (token_t*)malloc(sizeof(token_t) * TOKEN_ARRAY_ALLOC_SIZE);
  array->max_size = TOKEN_ARRAY_ALLOC_SIZE;
  array->size = 0;

  return array;
}

void destory_token_array(token_array_t* array) {
  while (array->size) {
    pop_token_array(array);
  }

  free(array);
}

void push_token_array(token_array_t* array, token_t token) {
  if (array->size >= array->max_size) {
    array->tokens = (token_t*)realloc(array->tokens,
                                      array->max_size + TOKEN_ARRAY_ALLOC_SIZE);

    array->max_size += TOKEN_ARRAY_ALLOC_SIZE;
  }

  array->tokens[array->size].type = token.type;
  array->tokens[array->size].val = token.val;
  array->size++;
}

token_t top_token_array(token_array_t* array) {
  if (array->size) {
    return array->tokens[array->size - 1];
  }

  throw_error("trying to top an empty token stack");

  token_t token;
  return token;
}

token_t pop_token_array(token_array_t* array) {
  token_t top_token = top_token_array(array);

  array->size--;

  return top_token;
}
