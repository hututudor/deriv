#include "line_array.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../utils/utils.h"

#define LINE_ARRAY_ALLOC_SIZE 100
#define LINE_ARRAY_CONTENT_ALLOC_SIZE 10000

line_array_t* init_line_array() {
  line_array_t* array = (line_array_t*)malloc(sizeof(line_array_t));

  array->lines = (line_t*)malloc(sizeof(line_t) * LINE_ARRAY_ALLOC_SIZE);
  array->max_size = LINE_ARRAY_ALLOC_SIZE;
  array->size = 0;

  return array;
}

void destory_line_array(line_array_t* array) {
  while (array->size) {
    pop_line_array(array);
  }

  free(array->lines);
  free(array);
}

void push_line_array(line_array_t* array, line_t line) {
  if (array->size >= array->max_size) {
    array->lines = (line_t*)realloc(
        array->lines,
        sizeof(line_t) * (array->max_size + LINE_ARRAY_ALLOC_SIZE));

    array->max_size += LINE_ARRAY_ALLOC_SIZE;
  }

  array->lines[array->size].color = line.color;
  array->lines[array->size].parent = line.parent;
  array->lines[array->size].child = line.child;

  array->size++;
}

line_t top_line_array(line_array_t* array) {
  if (array->size) {
    return array->lines[array->size - 1];
  }

  throw_error("trying to top an empty line stack");

  line_t line;
  return line;
}

line_t pop_line_array(line_array_t* array) {
  line_t top_line = top_line_array(array);

  array->size--;

  return top_line;
}

void render_line_array(void* context, line_array_t* array) {
  for (int i = 0; i < array->size; i++) {
    render_line(context, array->lines[i]);
  }
}