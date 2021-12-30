#include "derivaLN.h"

#include "../utils/utils.h"

void DerivaLN(node_t*& start) {
  if (start->token.type != TOKEN_LN || start->right != nullptr) {
    throw_error(
        "X derivation ERROR.\nThe program tries to derivate something which is "
        "not LN function");
  }

  node_t* multiplier = new node_t();
  multiplier->token.type = TOKEN_MUL;

  start->token.type = TOKEN_POW;

  node_t* negative1 = new node_t();
  negative1->token.type = TOKEN_NUMBER;
  negative1->token.val = -1;

  start->right = negative1;

  multiplier->left = start;

  node_t* fDerivat = new node_t();
  CopySubTree(start->left, fDerivat);
  Deriva(fDerivat);

  multiplier->right = fDerivat;

  start = multiplier;
}