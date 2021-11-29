#ifndef TOKEN_ARRAY_H
#define TOKEN_ARRAY_H

#include "../ast/ast.h"

typedef struct {
  token_t* tokens;
  int size;
  int max_size;
} token_array_t;

token_array_t* init_token_array();
void destory_token_array(token_array_t* array);

void push_token_array(token_array_t* array, token_t token);
token_t top_token_array(token_array_t* array);
token_t pop_token_array(token_array_t* array);

#endif