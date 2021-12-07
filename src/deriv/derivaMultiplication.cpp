#include "derivaMultiplication.h"

#include <cstdlib>

#include "../utils/utils.h"

void DerivaMultiplication(node_t *&start) {
  if (start->token.type != TOKEN_MUL) {
    throw_error(
        "ERROR. This is not a multiplication token, but it tries to apply "
        "multiplication rules.");
    return;
  }

  node_t *f = start->left;
  node_t *g = start->right;

  if (f == nullptr || g == nullptr) {
    throw_error("A multiplication must have 2 active functions.");
    return;
  }

  if (isNumber(f->token.type) == false) {
    if (isNumber(g->token.type) == false) {
      /// function1 * function2 derivat => function1Derivat*function2 +
      /// function1*function2Derivat
      node_t *plus = new node_t();
      plus->token.type = TOKEN_PLUS;

      node_t *firstMultiplier = new node_t();
      firstMultiplier->token.type = TOKEN_MUL;

      plus->left = firstMultiplier;
      plus->right = start;

      firstMultiplier->right = g;

      node_t *fderivat = new node_t();
      CopySubTree(f, fderivat);

      node_t *gderivat = new node_t();
      CopySubTree(g, gderivat);

      Deriva(fderivat);
      Deriva(gderivat);

      firstMultiplier->left = fderivat;
      start->right = gderivat;

      start = plus;
    } else {
      /// function * ct derivat => functionDerivat * ct
      Deriva(f);
      start->left = f;
    }
  } else if (isNumber(g->token.type) == false) {
    // ct*function derivat => ct*functionDerivat
    Deriva(g);
    start->right = g;
  } else {
    /// ct*ct derivat => 0
    start->token.type = TOKEN_NUMBER;
    start->token.val = 0;

    free(f);
    free(g);

    start->left = nullptr;
    start->right = nullptr;
    return;
  }
}