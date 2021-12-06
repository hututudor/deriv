#include "derivaSin.h"

#include "../utils/utils.h"

void DerivaSin(node_t*& start) {
  if (start->token.type != TOKEN_SIN) {
    throw_error(
        "ERROR. Trying to deriv a function which is NOT SIN with SIN rules.");
  }

  start->token.type = TOKEN_COS;

  node_t* fDerivat = new node_t();
  CopySubTree(start->left, fDerivat);

  Deriva(fDerivat);

  node_t* multiplier = new node_t();
  multiplier->token.type = TOKEN_MUL;
  multiplier->left = start;
  multiplier->right = fDerivat;

  start = multiplier;
}