#include "derivaDIV.h"

#include "../utils/utils.h"

void DerivaDIV(node_t*& start) {
  if (start->token.type != TOKEN_DIV) {
    throw_error(
        "X derivation ERROR.\nThe program tries to derivate something which is "
        "not X");
    return;
  }

  node_t* f = start->left;
  node_t* g = start->right;

  if (f == nullptr || g == nullptr) {
    throw_error("ERROR. Can't divide less then 2 functions.");
    return;
  }

  if (isNumber(f->token.type) == false) {
    if (isNumber(g->token.type) == false) {
      node_t* firstMultiplication = new node_t();
      firstMultiplication->token.type = TOKEN_MUL;

      node_t* secondMultiplication = new node_t();
      secondMultiplication->token.type = TOKEN_MUL;

      createFderivatMULG(start, firstMultiplication);
      createFMULGderivat(start, secondMultiplication);

      node_t* minus = new node_t();
      minus->token.type = TOKEN_MINUS;

      minus->left = firstMultiplication;
      minus->right = secondMultiplication;

      node_t* powPatrat = new node_t();
      powPatrat->token.type = TOKEN_POW;
      createPowPatrat(start, powPatrat);

      start->left = minus;
      start->right = powPatrat;
    } else {  /// F/nr
      start->token.type = TOKEN_MUL;
      g->token.val = 1 / g->token.val;
      Deriva(f);
      start->left = f;
    }
  } else {
    if (isNumber(g->token.type) == false) {  /// x/g
      start->token.type = TOKEN_MUL;

      node_t* pow = new node_t();
      pow->token.type = TOKEN_POW;
      pow->left = g;

      pow->right = new node_t();
      pow->right->token.type = TOKEN_NUMBER;
      pow->right->token.val = -1;

      start->right = pow;

    } else {
      /// Simplify-> ct/ct
    }
  }
}

void createPowPatrat(node_t* start, node_t*& powPatrat) {
  node_t* gCopy = new node_t();
  CopySubTree(start->right, gCopy);

  powPatrat->right = new node_t();
  powPatrat->right->token.type = TOKEN_NUMBER;
  powPatrat->right->token.val = 2;

  powPatrat->left = gCopy;
}

void createFMULGderivat(node_t* start, node_t*& secondMultiplication) {
  node_t* gDerivat = new node_t();
  CopySubTree(start->right, gDerivat);

  node_t* fCopy = new node_t();
  CopySubTree(start->left, fCopy);

  Deriva(gDerivat);

  secondMultiplication->left = fCopy;
  secondMultiplication->right = gDerivat;
}

void createFderivatMULG(node_t* start, node_t*& firstMultiplication) {
  node_t* gCopy = new node_t();
  CopySubTree(start->right, gCopy);

  node_t* fDerivat = new node_t();
  CopySubTree(start->left, fDerivat);

  Deriva(fDerivat);

  firstMultiplication->left = fDerivat;
  firstMultiplication->right = gCopy;
}