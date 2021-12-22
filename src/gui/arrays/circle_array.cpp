#include "circle_array.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../utils/utils.h"

#define CIRCLE_ARRAY_ALLOC_SIZE 100

circle_array_t* init_circle_array() {
  circle_array_t* array = (circle_array_t*)malloc(sizeof(circle_array_t));

  array->circles =
      (circle_t*)malloc(sizeof(circle_t) * CIRCLE_ARRAY_ALLOC_SIZE);
  array->max_size = CIRCLE_ARRAY_ALLOC_SIZE;
  array->size = 0;

  return array;
}

void destory_circle_array(circle_array_t* array) {
  while (array->size) {
    pop_circle_array(array);
  }

  free(array->circles);
  free(array);
}

void push_circle_array(circle_array_t* array, circle_t circle) {
  if (array->size >= array->max_size) {
    array->circles = (circle_t*)realloc(
        array->circles,
        sizeof(circle_t) * (array->max_size + CIRCLE_ARRAY_ALLOC_SIZE));

    array->max_size += CIRCLE_ARRAY_ALLOC_SIZE;
  }

  array->circles[array->size].border_color = circle.border_color;
  array->circles[array->size].center_pos = circle.center_pos;
  array->circles[array->size].radius = circle.radius;
  array->circles[array->size].background = circle.background;
  array->size++;
}

circle_t top_circle_array(circle_array_t* array) {
  if (array->size) {
    return array->circles[array->size - 1];
  }

  throw_error("trying to top an empty circle stack");

  circle_t circle;
  return circle;
}

circle_t pop_circle_array(circle_array_t* array) {
  circle_t top_circle = top_circle_array(array);

  array->size--;

  return top_circle;
}

void render_circle_array(void* context, circle_array_t* array) {
  for (int i = 0; i < array->size; i++) {
    render_circle(context, array->circles[i]);
  }
}