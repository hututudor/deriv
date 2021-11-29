#ifndef AST_NODE_ARRAY_H
#define AST_NODE_ARRAY_H

#include "../ast/ast.h"

typedef struct {
  node_t* nodes;
  int size;
  int max_size;
} ast_node_array_t;

ast_node_array_t* init_ast_node_array();
void destory_ast_node_array(ast_node_array_t* array);

void push_ast_node_array(ast_node_array_t* array, node_t node);
node_t top_ast_node_array(ast_node_array_t* array);
node_t pop_ast_node_array(ast_node_array_t* array);

node_t* make_node(node_t node);

#endif