#include "ast_node_array.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define AST_ARRAY_ALLOC_SIZE 100

ast_node_array_t* init_ast_node_array() {
  ast_node_array_t* array = (ast_node_array_t*)malloc(sizeof(ast_node_array_t));

  array->nodes = (node_t*)malloc(sizeof(node_t) * AST_ARRAY_ALLOC_SIZE);
  array->max_size = AST_ARRAY_ALLOC_SIZE;
  array->size = 0;

  return array;
}

void destory_ast_node_array(ast_node_array_t* array) {
  while (array->size) {
    pop_ast_node_array(array);
  }

  free(array->nodes);
  free(array);
}

void push_ast_node_array(ast_node_array_t* array, node_t node) {
  if (array->size >= array->max_size) {
    array->nodes = (node_t*)realloc(
        array->nodes,
        sizeof(node_t) * (array->max_size + AST_ARRAY_ALLOC_SIZE));

    array->max_size += AST_ARRAY_ALLOC_SIZE;
  }

  array->nodes[array->size].left = node.left;
  array->nodes[array->size].right = node.right;
  array->nodes[array->size].token.type = node.token.type;
  array->nodes[array->size].token.val = node.token.val;
  array->size++;
}

node_t top_ast_node_array(ast_node_array_t* array) {
  if (array->size) {
    return array->nodes[array->size - 1];
  }

  throw_error("trying to top an empty ast node stack");

  node_t token;
  return token;
}

node_t pop_ast_node_array(ast_node_array_t* array) {
  node_t top_node = top_ast_node_array(array);

  array->size--;

  return top_node;
}

node_t* make_node(node_t node) {
  node_t* pnode = (node_t*)malloc(sizeof(node_t));

  pnode->left = node.left;
  pnode->right = node.right;
  pnode->token.type = node.token.type;
  pnode->token.val = node.token.val;

  return pnode;
}