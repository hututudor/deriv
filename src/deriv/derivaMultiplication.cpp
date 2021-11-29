#include "derivaMultiplication.h"

void DerivaMultiplication(node_t *&start) {
  if (start->token.type != TOKEN_MUL) {
    return;  /// ERROR
  }

  node_t *f = start->left;
  node_t *g = start->right;

  if (f == nullptr || g == nullptr) {
    return;  /// ERROR
  }

  if (isNumber(f->token.type) == false) {
    if (isNumber(g->token.type) == false) {
      node_t *plus = new node_t();
      plus->token.type = TOKEN_PLUS;

      node_t *firstMultiplier = new node_t();
      firstMultiplier->token.type = TOKEN_MUL;
      /// second multiplier is in start variable;

      node_t *fderivat = new node_t();
      CopySubTree(f, fderivat);

      node_t *gderivat = new node_t();
      CopySubTree(g, gderivat);

      Deriva(fderivat);
      Deriva(gderivat);

      plus->left = firstMultiplier;
      plus->right = start;

      firstMultiplier->left = fderivat;
      firstMultiplier->right = g;

      start->right = gderivat;

      start = plus;
    } else {
      Deriva(f);
    }
  } else if (isNumber(g->token.type) == false)  // f este ct => derivam doar g
  {
    Deriva(g);
  } else  /// ambele functii sunt ct => nu facem nimic, este o inmultire intre
          /// ct
  {
    // Simplify(f,g) daca ambele sunt numere si nu e
    return;
  }
}