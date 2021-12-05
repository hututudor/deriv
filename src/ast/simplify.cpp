#include "simplify.h"

#include <stdio.h>
#include <stdlib.h>

#define APPLY_RULE(f)    \
  if (f(ast, new_ast)) { \
    return new_ast;      \
  }

bool rule_pow_1(node_t* ast, node_t*& new_ast) {
  if (!(ast->token.type == TOKEN_POW && ast->right &&
        ast->right->token.type == TOKEN_NUMBER && ast->right->token.val == 1)) {
    return false;
  }

  new_ast = clone_ast(ast->left);

  return true;
}

node_t* simplify_ast(node_t* ast) {
  if (!ast) return nullptr;

  ast->left = simplify_ast(ast->left);
  ast->right = simplify_ast(ast->right);

  node_t* new_ast = nullptr;

  APPLY_RULE(rule_pow_1);

  return clone_ast(ast);
}