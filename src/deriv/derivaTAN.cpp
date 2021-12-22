#include "derivaTan.h"

#include "../utils/utils.h"

void DerivaTan(node_t*& start) {
  if (start->token.type != TOKEN_TAN) {
    throw_error(
        "ERROR. Trying to deriv a function which is NOT TAN with TAN rules.");
  }

  node_t* f = start->left;

  node_t* mul = new node_t();
  mul->token.type = TOKEN_MUL;

  node_t* fDerivat = new node_t();
  CopySubTree(f, fDerivat);
  Deriva(fDerivat);

  mul->right = fDerivat;
  mul->left = start;

  start->token.type = TOKEN_DIV;

  start->left = new node_t();
  start->left->token.type = TOKEN_NUMBER;
  start->left->token.val = 1;

  node_t* pow = new node_t();
  pow->token.type = TOKEN_POW;

  pow->right = new node_t();
  pow->right->token.type = TOKEN_NUMBER;
  pow->right->token.val = 2;

  pow->left = new node_t();
  pow->left->token.type = TOKEN_COS;

  start->right = pow;

  pow->left->left = f;

  start = mul;
}