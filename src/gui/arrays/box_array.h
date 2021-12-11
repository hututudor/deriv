#ifndef BOX_ARRAY_H
#define BOX_ARRAY_H

#include "../components/box.h"

typedef struct {
  box_t* boxes;
  int size;
  int max_size;
} box_array_t;

box_array_t* init_box_array();
void destory_box_array(box_array_t* array);

void push_box_array(box_array_t* array, box_t box);
box_t top_box_array(box_array_t* array);
box_t pop_box_array(box_array_t* array);

void render_box_array(void* context, box_array_t* array);

#endif