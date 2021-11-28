#ifndef GLOBAL_H
#define GLOBAL_H

#define Nmax 1005

#include <cstddef>

enum token_type {
  TOKEN_0 = 0,
  TOKEN_NUMBER = 1,
  TOKEN_X = 2,
  TOKEN_PLUS = 3,
  TOKEN_MINUS = 4,
  TOKEN_MUL = 5,
  TOKEN_DIV = 6, 
  TOKEN_POW = 7,
  TOKEN_LN = 8,
  TOKEN_LG = 9,
  TOKEN_LOG = 10,
  TOKEN_COS = 11,
  TOKEN_SIN = 12,
  TOKEN_TAN = 13,
  TOKEN_COTAN = 14,
  TOKEN_E = 15,
  TOKEN_SQRT = 16,
  TOKEN_ARCSIN = 17,
  TOKEN_ARCCOS = 18,
  TOKEN_ARCCOTAN = 19,
  TOKEN_ARCTAN = 20
};

struct token_t{
  token_type type;
  double val;
};

struct node_t {
  token_t token;
  node_t *left, *right;

  node_t()
  {
    this->token.type = TOKEN_0;
    this->left = NULL;
    this->right = NULL;
  }
};

void Deriva(node_t *&start);

token_type GetTokenType(int token);
bool isNumber(token_type token);

void CopySubTree(node_t* from, node_t*& to);

#endif