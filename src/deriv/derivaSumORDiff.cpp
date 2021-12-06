#include "derivaSumORDiff.h"

#include <cstdlib>

#include "../utils/utils.h"

void DerivaSumOrDiff(node_t*& start) {
  if (start->token.type != TOKEN_PLUS && start->token.type != TOKEN_MINUS) {
    throw_error("Not a SUM or DIFFERENCE sign. ERROR At dividing",
                start->token.type);
  }

  node_t* f = start->left;
  node_t* g = start->right;

  if (f == nullptr || g == nullptr) {
    throw_error("Sum or Difference with only 1 nr. ERROR");
  }

  if (isNumber(f->token.type) == false) {
    if (isNumber(g->token.type) == false) {
      Deriva(f);
      Deriva(g);

      start->left = f;
      start->right = g;

    } else {
      Deriva(f);
      free(g);
      start = f;
    }
  } else {
    if (isNumber(g->token.type) == false) {
      Deriva(g);
      free(f);
      start = g;
    } else {
      /// Simplify -> suma/diff intre doua constante (?)
    }
  }
}