#ifndef NODE_ARRAY_H
#define NODE_ARRAY_H

#include "../components/node.h"

typedef struct {
  gui_node_t* nodes;
  int size;
  int max_size;
} node_array_t;

node_array_t* init_node_array();
void destory_node_array(node_array_t* array);

void push_node_array(node_array_t* array, gui_node_t node);
gui_node_t top_node_array(node_array_t* array);
gui_node_t pop_node_array(node_array_t* array);

void update_node_array(void* context, node_array_t* array);
void render_node_array(void* context, node_array_t* array);

#endif