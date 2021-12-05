#include "../utils/utils.h"
#include "derivaLN.h"

void DerivaLN(node_t*& start) {
  if (start->token.type != TOKEN_LN || start->right != nullptr) {
    throw_error(
        "X derivation ERROR.\nThe program tries to derivate something which is "
        "not LN function");
  }

  start->token.type = TOKEN_POW;

  node_t* negative1 = new node_t();
  negative1->token.type = TOKEN_NUMBER;
  negative1->token.val = -1;

  start->right = negative1;
}