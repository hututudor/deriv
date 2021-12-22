#ifndef CIRCLE_ARRAY_H
#define CIRCLE_ARRAY_H

#include "../components/circle.h"

typedef struct {
  circle_t* circles;
  int size;
  int max_size;
} circle_array_t;

circle_array_t* init_circle_array();
void destory_circle_array(circle_array_t* array);

void push_circle_array(circle_array_t* array, circle_t circle);
circle_t top_circle_array(circle_array_t* array);
circle_t pop_circle_array(circle_array_t* array);

void render_circle_array(void* context, circle_array_t* array);

#endif