#ifndef INPUT_ARRAY_H
#define INPUT_ARRAY_H

#include "../components/input.h"

typedef struct {
  input_t* inputs;
  int size;
  int max_size;
} input_array_t;

input_array_t* init_input_array();
void destory_input_array(input_array_t* array);

void push_input_array(input_array_t* array, input_t input);
input_t top_input_array(input_array_t* array);
input_t pop_input_array(input_array_t* array);

void update_input_array(void* context, input_array_t* array);
void render_input_array(void* context, input_array_t* array);

#endif