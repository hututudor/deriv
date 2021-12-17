#include "derivaPow.h"

#include <cstdlib>

#include "../utils/utils.h"
void DerivaPow(node_t *&start) {
  if (start->token.type != TOKEN_POW) {
    throw_error(
        "ERROR! Trying to deriv a function which is not POW with POW rules.");
  }

  node_t *f = start->left;
  node_t *g = start->right;

  if (f == nullptr || g == nullptr) {
    throw_error(
        "ERROR. Trying to deriv a POW function with less then 2 parameters");
  }

  if (isNumber(f->token.type) == false) {
    if (isNumber(g->token.type) == false)  // expresie la expresie
    {
      node_t *multiplier = new node_t();
      multiplier->token.type = TOKEN_MUL;

      node_t *sum = new node_t();
      sum->token.type = TOKEN_PLUS;

      multiplier->left = start;
      multiplier->right = sum;

      node_t *fderivat = new node_t();
      CopySubTree(f, fderivat);

      node_t *gderivat = new node_t();
      CopySubTree(g, gderivat);

      Deriva(fderivat);
      Deriva(gderivat);

      node_t *secondMultiplier = new node_t();
      secondMultiplier->token.type = TOKEN_MUL;

      secondMultiplier->left = fderivat;
      secondMultiplier->right = new node_t();
      secondMultiplier->right->token.type = TOKEN_DIV;

      node_t *gCopy = new node_t();
      CopySubTree(g, gCopy);
      secondMultiplier->right->left = gCopy;

      node_t *fCopy = new node_t();
      CopySubTree(f, fCopy);
      secondMultiplier->right->right = fCopy;

      sum->left = secondMultiplier;  ///

      node_t *thirdMultiplier = new node_t();
      thirdMultiplier->token.type = TOKEN_MUL;

      thirdMultiplier->left = gderivat;
      thirdMultiplier->right = new node_t();
      thirdMultiplier->right->token.type = TOKEN_LN;
      thirdMultiplier->right->left = new node_t();
      node_t *secondFCopy = new node_t();
      CopySubTree(f, secondFCopy);
      thirdMultiplier->right->left = secondFCopy;

      sum->right = thirdMultiplier;  ///
      start = multiplier;
    } else  // expresie la constanta
    {
      node_t *firstMultiply = new node_t();
      firstMultiply->token.type = TOKEN_MUL;
      node_t *secondMultiply = new node_t();
      secondMultiply->token.type = TOKEN_MUL;

      node_t *fderivat = new node_t();
      CopySubTree(f, fderivat);

      double ct = g->token.val;

      Deriva(fderivat);

      firstMultiply->right = fderivat;
      firstMultiply->left = secondMultiply;

      secondMultiply->left = new node_t();
      secondMultiply->left->token.type = TOKEN_NUMBER;
      secondMultiply->left->token.val = ct;

      secondMultiply->right = start;
      start->right->token.val--;

      start = firstMultiply;
    }
  } else {
    if (isNumber(g->token.type) == false)  /// constanta la expresie
    {
      node_t *firstMultiply = new node_t();
      node_t *gDerivat = new node_t();

      CopySubTree(g, gDerivat);

      firstMultiply->right = gDerivat;

      if (f->token.type == TOKEN_E) {
        firstMultiply->left = start;
      } else {
        node_t *secondMultiply = new node_t();
        secondMultiply->left = start;

        secondMultiply->right = new node_t();
        secondMultiply->right->token.type = TOKEN_LN;

        secondMultiply->right->left = new node_t();
        secondMultiply->right->left->token.type = TOKEN_NUMBER;
        secondMultiply->right->left->token.val = f->token.val;

        firstMultiply->left = secondMultiply;
      }
      start = firstMultiply;
    } else  /// constanta la constanta
    {
      start->token.type = TOKEN_NUMBER;
      start->token.val = 0;

      free(f);
      free(g);

      start->left = nullptr;
      start->right = nullptr;
      return;
    }
  }

  return;
}