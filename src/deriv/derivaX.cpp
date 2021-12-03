#include "derivaX.h"

#include "../utils/utils.h"

void DerivaX(node_t*& start) {
  if (start->token.type != TOKEN_X) {
    throw_error(
        "X derivation ERROR.\nThe program tries to derivate something which is "
        "not X");
    return;
  }

  start->token.type = TOKEN_NUMBER;
  start->token.val = 1;
}