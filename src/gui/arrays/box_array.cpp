#include "box_array.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../utils/utils.h"

#define BOX_ARRAY_ALLOC_SIZE 100

box_array_t* init_box_array() {
  box_array_t* array = (box_array_t*)malloc(sizeof(box_array_t));

  array->boxes = (box_t*)malloc(sizeof(box_t) * BOX_ARRAY_ALLOC_SIZE);
  array->max_size = BOX_ARRAY_ALLOC_SIZE;
  array->size = 0;

  return array;
}

void destory_box_array(box_array_t* array) {
  while (array->size) {
    pop_box_array(array);
  }

  free(array->boxes);
  free(array);
}

void push_box_array(box_array_t* array, box_t box) {
  if (array->size >= array->max_size) {
    array->boxes = (box_t*)realloc(
        array->boxes, sizeof(box_t) * (array->max_size + BOX_ARRAY_ALLOC_SIZE));

    array->max_size += BOX_ARRAY_ALLOC_SIZE;
  }

  array->boxes[array->size].color = box.color;
  array->boxes[array->size].pos = box.pos;
  array->boxes[array->size].size = box.size;
  array->size++;
}

box_t top_box_array(box_array_t* array) {
  if (array->size) {
    return array->boxes[array->size - 1];
  }

  throw_error("trying to top an empty box stack");

  box_t box;
  return box;
}

box_t pop_box_array(box_array_t* array) {
  box_t top_box = top_box_array(array);

  array->size--;

  return top_box;
}

void render_box_array(void* context, box_array_t* array) {
  for (int i = 0; i < array->size; i++) {
    render_box(context, array->boxes[i]);
  }
}