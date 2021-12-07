#include "derivaLG.h"

#include "../utils/utils.h"

void DerivaLG(node_t*& start) {
  if (start->token.type != TOKEN_LG || start->right != nullptr) {
    throw_error(
        "X derivation ERROR.\nThe program tries to derivate something which is "
        "not LN function");
  }

  start->token.type = TOKEN_DIV;
  start->left->token.type = TOKEN_NUMBER;
  start->left->token.val = 1;

  node_t* multiplier = new node_t();
  multiplier->token.type = TOKEN_MUL;

  multiplier->left = new node_t();
  multiplier->left->token.type = TOKEN_X;

  multiplier->right = new node_t();
  multiplier->right->token.type = TOKEN_LN;

  multiplier->right->left = new node_t();
  multiplier->right->left->token.type = TOKEN_NUMBER;
  multiplier->right->left->token.val = 10;

  start->right = multiplier;
}