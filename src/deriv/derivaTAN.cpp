#include "derivaTAN.h"

#include "../utils/utils.h"

void DerivaTAN(node_t*& start) {
  if (start->token.type != TOKEN_TAN) {
    throw_error(
        "ERROR. Trying to deriv a function which is NOT TAN with TAN rules.");
  }
}