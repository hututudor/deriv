#include "input_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/utils.h"

#define INPUT_ARRAY_ALLOC_SIZE 100
#define INPUT_ARRAY_CONTENT_ALLOC_SIZE 10000

input_array_t* init_input_array() {
  input_array_t* array = (input_array_t*)malloc(sizeof(input_array_t));

  array->inputs = (input_t*)malloc(sizeof(input_t) * INPUT_ARRAY_ALLOC_SIZE);
  array->max_size = INPUT_ARRAY_ALLOC_SIZE;
  array->size = 0;

  return array;
}

void destory_input_array(input_array_t* array) {
  while (array->size) {
    pop_input_array(array);
  }

  free(array->inputs);
  free(array);
}

void push_input_array(input_array_t* array, input_t input) {
  if (array->size >= array->max_size) {
    array->inputs = (input_t*)realloc(
        array->inputs,
        sizeof(input_t) * (array->max_size + INPUT_ARRAY_ALLOC_SIZE));

    array->max_size += INPUT_ARRAY_ALLOC_SIZE;
  }

  array->inputs[array->size].color = input.color;
  array->inputs[array->size].background = input.background;
  array->inputs[array->size].pos = input.pos;
  array->inputs[array->size].size = input.size;
  array->inputs[array->size].font_size = input.font_size;
  array->inputs[array->size].text = input.text;
  array->inputs[array->size].is_focused = false;
  array->inputs[array->size].prev_pressed = false;
  array->inputs[array->size].callback = input.callback;
  array->inputs[array->size].content =
      (char*)calloc(1, INPUT_ARRAY_CONTENT_ALLOC_SIZE);

  array->size++;
}

input_t top_input_array(input_array_t* array) {
  if (array->size) {
    return array->inputs[array->size - 1];
  }

  throw_error("trying to top an empty input stack");

  input_t input;
  return input;
}

input_t pop_input_array(input_array_t* array) {
  input_t top_input = top_input_array(array);

  array->size--;

  return top_input;
}

void update_input_array(void* context, input_array_t* array) {
  for (int i = 0; i < array->size; i++) {
    update_input(context, array->inputs[i]);
  }
}

void render_input_array(void* context, input_array_t* array) {
  for (int i = 0; i < array->size; i++) {
    render_input(context, array->inputs[i]);
  }
}