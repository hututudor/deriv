
#include "ast_gui_utils.h"

#include <stdio.h>
#include <stdlib.h>

#include <queue>
#include <utility>

#include "../../utils/utils.h"

location_array_t* init_location_array(int size) {
  location_array_t* array = (location_array_t*)malloc(sizeof(location_array_t));

  array->locations = (node_location_t*)malloc(sizeof(node_location_t) * size);
  array->max_size = size;
  array->size = 0;
  return array;
}

node_location_t top_location_array(location_array_t* array) {
  if (array->size) {
    return array->locations[array->size - 1];
  }

  throw_error("trying to top an empty location stack");

  node_location_t location;
  return location;
}

node_location_t pop_location_array(location_array_t* array) {
  node_location_t top_location = top_location_array(array);

  array->size--;

  return top_location;
}

void destory_location_array(location_array_t* array) {
  while (array->size) {
    pop_location_array(array);
  }

  free(array->locations);
  free(array);
}

void push_location_array(location_array_t* array, node_location_t* location) {
  if (array->size >= array->max_size) {
    array->locations = (node_location_t*)realloc(
        array->locations, sizeof(node_location_t) *
                              (array->max_size + LOCATION_ARRAY_ALLOC_SIZE));

    array->max_size += LOCATION_ARRAY_ALLOC_SIZE;
  }

  array->locations[array->size].node = location->node;
  array->locations[array->size].column = location->column;
  array->locations[array->size].row = location->row;
  array->size++;
}

void GetTreeSize(node_t* ast, int& columnCounter, int& rowCounter) {
  std::queue<std::pair<node_t*, int>> q;

  q.push({ast, 1});
  columnCounter = 1;

  int maxHight = 0;

  while (!q.empty()) {
    std::pair<node_t*, int> p = q.front();
    q.pop();

    node_t* node = p.first;
    int depth = p.second;

    if (depth > maxHight) {
      maxHight = depth;
    }

    if (node->left != nullptr) {
      q.push({node->left, depth + 1});
      columnCounter++;
    }

    if (node->right != nullptr) {
      q.push({node->right, depth + 1});
      columnCounter++;
    }
  }

  rowCounter = maxHight;
}

void FillArray(location_array_t* array, node_t* root, int& column, int& row,
               bool& foundIndex, int columnSetUp) {
  if (root->left == nullptr && root->right == nullptr) {
    if (foundIndex == false) {
      foundIndex = true;
      column = columnSetUp;
    }
  }

  if (root->left != nullptr) {
    column--;
    row++;
    FillArray(array, root->left, column, row, foundIndex, columnSetUp);
    column++;
    row--;
  }

  node_location_t* newLocation =
      (node_location_t*)malloc(sizeof(node_location_t));
  newLocation->node = root;
  newLocation->column = column;
  newLocation->row = row;

  push_location_array(array, newLocation);

  if (root->right != nullptr) {
    foundIndex = false;
    columnSetUp = column + 1;
    row++;
    FillArray(array, root->right, column, row, foundIndex, columnSetUp);
    row--;
  }
}

location_array_t* Get_GuiNode_Locations(node_t* ast, int columnCounter,
                                        int rowCounter) {
  location_array_t* array = init_location_array(columnCounter);
  int startingColumn = 0;
  int startingRow = 0;
  bool foundIndex = false;
  int columnSetUp = 0;

  FillArray(array, ast, startingColumn, startingRow, foundIndex, columnSetUp);

  return array;
}

location_array_t* Get_GuiNode_Locations(node_t* ast) {
  int columnCounter = 0;
  int rowCounter = 0;

  GetTreeSize(ast, columnCounter, rowCounter);

  return Get_GuiNode_Locations(ast, columnCounter, rowCounter);
}
