#include "derivaSqrt.h"

#include "../utils/utils.h"

void DerivaSqrt(node_t*& start) {
  if (start->token.type != TOKEN_SQRT) {
    throw_error(
        "ERROR. Trying to derivate something which is not SQRT with SQRT "
        "rules");
  }

  node_t* f = start->left;

  node_t* fDerivat = new node_t();
  CopySubTree(f, fDerivat);
  Deriva(fDerivat);

  node_t* mul = new node_t();
  mul->token.type = TOKEN_MUL;

  mul->right = fDerivat;

  node_t* div = new node_t();
  div->token.type = TOKEN_DIV;

  /// numarator: 1
  div->left = new node_t();
  div->left->token.type = TOKEN_NUMBER;
  div->left->token.val = 1;

  /// numitor: 2*f (sqrt(x))
  div->right = new node_t();
  div->right->token.type = TOKEN_MUL;

  div->right->left = new node_t();
  div->right->left->token.type = TOKEN_NUMBER;
  div->right->left->token.val = 2;

  div->right->right = start;

  mul->left = div;

  start = mul;
}