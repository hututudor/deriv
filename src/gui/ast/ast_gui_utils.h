#ifndef AST_GUI_UTILS_H
#define AST_GUI_UTILS_H

#include "../../ast/ast.h"
#define LOCATION_ARRAY_ALLOC_SIZE 100

typedef struct {
  int column;
  int row;
} cell_t;
typedef struct {
  node_t* node;
  cell_t* current;
  cell_t* left;
  cell_t* right;
} node_location_t;
typedef struct {
  node_location_t* locations;
  int size;
  int max_size;
} location_array_t;

location_array_t* Get_GuiNode_Locations(node_t* ast);
location_array_t* Get_GuiNode_Locations(node_t* ast, int columnCounter,
                                        int rowCounter);

node_location_t top_location_array(location_array_t* array);
node_location_t pop_location_array(location_array_t* array);

void destory_location_array(location_array_t* array);

void GetTreeSize(node_t* ast, int& columnCounter, int& rowCounter);

#endif