#include "node_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/utils.h"

#define NODE_ARRAY_ALLOC_SIZE 100

node_array_t* init_node_array() {
  node_array_t* array = (node_array_t*)malloc(sizeof(node_array_t));

  array->nodes =
      (gui_node_t*)malloc(sizeof(gui_node_t) * NODE_ARRAY_ALLOC_SIZE);
  array->max_size = NODE_ARRAY_ALLOC_SIZE;
  array->size = 0;

  return array;
}

void destory_node_array(node_array_t* array) {
  while (array->size) {
    pop_node_array(array);
  }

  free(array->nodes);
  free(array);
}

void push_node_array(node_array_t* array, gui_node_t node) {
  if (array->size >= array->max_size) {
    array->nodes = (gui_node_t*)realloc(
        array->nodes,
        sizeof(gui_node_t) * (array->max_size + NODE_ARRAY_ALLOC_SIZE));

    array->max_size += NODE_ARRAY_ALLOC_SIZE;
  }

  array->nodes[array->size].border_color = node.border_color;
  array->nodes[array->size].background = node.background;
  array->nodes[array->size].center_pos = node.center_pos;
  array->nodes[array->size].font_size = node.font_size;
  array->nodes[array->size].radius = node.radius;
  array->nodes[array->size].text_color = node.text_color;

  array->nodes[array->size].content = (char*)malloc(100000);
  strcpy(array->nodes[array->size].content, node.content);

  array->size++;
}

gui_node_t top_node_array(node_array_t* array) {
  if (array->size) {
    return array->nodes[array->size - 1];
  }

  throw_error("trying to top an empty node stack");

  gui_node_t node;
  return node;
}

gui_node_t pop_node_array(node_array_t* array) {
  gui_node_t top_node = top_node_array(array);

  array->size--;

  return top_node;
}

void update_node_array(void* context, node_array_t* array) {
  for (int i = 0; i < array->size; i++) {
    update_node(context, array->nodes[i]);
  }
}

void render_node_array(void* context, node_array_t* array) {
  for (int i = 0; i < array->size; i++) {
    render_node(context, array->nodes[i]);
  }
}