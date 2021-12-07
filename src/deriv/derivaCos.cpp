#include "derivaCos.h"

#include "../utils/utils.h"

void DerivaCos(node_t*& start) {
  if (start->token.type != TOKEN_COS) {
    throw_error(
        "ERROR. Trying to deriv a function which is NOT COS with COS rules.");
  }

  start->token.type = TOKEN_SIN;

  node_t* fDerivat = new node_t();
  CopySubTree(start->left, fDerivat);

  Deriva(fDerivat);

  node_t* minus = new node_t();
  minus->token.type = TOKEN_MINUS;

  minus->left = new node_t();
  minus->left->token.type = TOKEN_NUMBER;
  minus->left->token.val = 0;

  minus->right = start;

  node_t* multiplier = new node_t();
  multiplier->token.type = TOKEN_MUL;
  multiplier->left = minus;
  multiplier->right = fDerivat;

  start = multiplier;
}