#ifndef BUTTON_ARRAY_H
#define BUTTON_ARRAY_H

#include "../components/button.h"

typedef struct {
  button_t* buttons;
  int size;
  int max_size;
} button_array_t;

button_array_t* init_button_array();
void destory_button_array(button_array_t* array);

void push_button_array(button_array_t* array, button_t button);
button_t top_button_array(button_array_t* array);
button_t pop_button_array(button_array_t* array);

void update_button_array(void* context, button_array_t* array);

#endif