#include "derivaArccotan.h"

#include "../utils/utils.h"

void DerivaArccotan(node_t*& start) {
  if (start->token.type != TOKEN_ARCCOTAN) {
    throw_error(
        "ERROR. Trying to derivate something which is not ARCCOTAN with "
        "ARCCOTAN "
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
  div->right->token.type = TOKEN_PLUS;

  node_t* plus = div->right;

  plus->left = new node_t();
  plus->left->token.type = TOKEN_NUMBER;
  plus->left->token.val = 1;

  start->token.type = TOKEN_POW;
  start->right = new node_t();
  start->right->token.type = TOKEN_NUMBER;
  start->right->token.val = 2;

  plus->right = start;

  start = mul;
}