#ifndef GLOBAL_H
#define GLOBAL_H

#include "ast.h"

#define Nmax 1005

void Deriva(node_t*& start);

bool isNumber(token_type token);

void CopySubTree(node_t* from, node_t*& to);

#endif