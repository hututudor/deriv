#include "simplify.h"

#include <stdio.h>
#include <stdlib.h>

#define APPLY_RULE(f) \
  if (f(ast)) {       \
    return;           \
  }

bool rule_pow_1(node_t*& ast) {
  if (!(ast->token.type == TOKEN_POW && ast->right &&
        ast->right->token.type == TOKEN_NUMBER && ast->right->token.val == 1)) {
    return false;
  }

  node_t* left = clone_ast(ast->left);

  destroy_ast(ast);

  ast = left;

  return true;
}

bool rule_pow_0(node_t*& ast) {
  if (!(ast->token.type == TOKEN_POW && ast->right &&
        ast->right->token.type == TOKEN_NUMBER && ast->right->token.val == 0)) {
    return false;
  }

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_NUMBER;
  ast->token.val = 1;

  ast->left = nullptr;
  ast->right = nullptr;

  return true;
}

void simplify_ast(node_t*& ast) {
  if (!ast) return;

  simplify_ast(ast->left);
  simplify_ast(ast->right);

  APPLY_RULE(rule_pow_1);
  APPLY_RULE(rule_pow_0);
}