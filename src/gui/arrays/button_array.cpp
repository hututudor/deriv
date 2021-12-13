#include "button_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/utils.h"

#define BUTTON_ARRAY_ALLOC_SIZE 100

button_array_t* init_button_array() {
  button_array_t* array = (button_array_t*)malloc(sizeof(button_array_t));

  array->buttons =
      (button_t*)malloc(sizeof(button_t) * BUTTON_ARRAY_ALLOC_SIZE);
  array->max_size = BUTTON_ARRAY_ALLOC_SIZE;
  array->size = 0;

  return array;
}

void destory_button_array(button_array_t* array) {
  while (array->size) {
    pop_button_array(array);
  }

  free(array->buttons);
  free(array);
}

void push_button_array(button_array_t* array, button_t button) {
  if (array->size >= array->max_size) {
    array->buttons = (button_t*)realloc(
        array->buttons,
        sizeof(button_t) * (array->max_size + BUTTON_ARRAY_ALLOC_SIZE));

    array->max_size += BUTTON_ARRAY_ALLOC_SIZE;
  }

  array->buttons[array->size].color = button.color;
  array->buttons[array->size].background = button.background;
  array->buttons[array->size].pos = button.pos;
  array->buttons[array->size].size = button.size;
  array->buttons[array->size].font_size = button.font_size;
  array->buttons[array->size].callback = button.callback;
  array->buttons[array->size].label = (char*)malloc(strlen(button.label) + 1);

  strcpy(array->buttons[array->size].label, button.label);

  array->size++;
}

button_t top_button_array(button_array_t* array) {
  if (array->size) {
    return array->buttons[array->size - 1];
  }

  throw_error("trying to top an empty button stack");

  button_t button;
  return button;
}

button_t pop_button_array(button_array_t* array) {
  button_t top_button = top_button_array(array);

  array->size--;

  return top_button;
}

void update_button_array(void* context, button_array_t* array) {
  for (int i = 0; i < array->size; i++) {
    update_button(context, array->buttons[i]);
  }
}