#include "derivaArccos.h"

#include "../utils/utils.h"

void DerivaArccos(node_t*& start) {
  if (start->token.type != TOKEN_ARCCOS) {
    throw_error(
        "ERROR. Trying to derivate something which is not ARCCOS with ARCCOS "
        "derivation rules");
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

  mul->left = div;

  div->left = new node_t();
  div->left->token.type = TOKEN_NUMBER;
  div->left->token.val = -1;

  div->right = new node_t();
  div->right->token.type = TOKEN_SQRT;

  div->right->left = new node_t();
  div->right->left->token.type = TOKEN_MINUS;

  node_t* minus = div->right->left;

  minus->left = new node_t();
  minus->left->token.type = TOKEN_NUMBER;
  minus->left->token.val = 1;

  start->token.type = TOKEN_POW;
  start->right = new node_t();
  start->right->token.type = TOKEN_NUMBER;
  start->right->token.val = 2;

  minus->right = start;

  start = mul;
}