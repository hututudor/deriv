#ifndef AST_GUI_UTILS_H
#define AST_GUI_UTILS_H

#include "../../ast/ast.h"

int ComputeTreeColumns(node_t* ast, int& startingColumn);
int ComputeTreeRows(node_t* ast);

#endif