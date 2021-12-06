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

bool rule_mul_0_rhs(node_t*& ast) {
  if (!(ast->token.type == TOKEN_MUL && ast->right &&
        ast->right->token.type == TOKEN_NUMBER && ast->right->token.val == 0)) {
    return false;
  }

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_NUMBER;
  ast->token.val = 0;

  ast->left = nullptr;
  ast->right = nullptr;

  return true;
}

bool rule_mul_0_lhs(node_t*& ast) {
  if (!(ast->token.type == TOKEN_MUL && ast->left &&
        ast->left->token.type == TOKEN_NUMBER && ast->left->token.val == 0)) {
    return false;
  }

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_NUMBER;
  ast->token.val = 0;

  ast->left = nullptr;
  ast->right = nullptr;

  return true;
}

bool rule_mul_1_rhs(node_t*& ast) {
  if (!(ast->token.type == TOKEN_MUL && ast->right &&
        ast->right->token.type == TOKEN_NUMBER && ast->right->token.val == 1)) {
    return false;
  }

  node_t* left = clone_ast(ast->left);

  destroy_ast(ast);

  ast = left;

  return true;
}

bool rule_mul_1_lhs(node_t*& ast) {
  if (!(ast->token.type == TOKEN_MUL && ast->left &&
        ast->left->token.type == TOKEN_NUMBER && ast->left->token.val == 1)) {
    return false;
  }

  node_t* right = clone_ast(ast->right);

  destroy_ast(ast);

  ast = right;

  return true;
}

void simplify_ast(node_t*& ast) {
  if (!ast) return;

  simplify_ast(ast->left);
  simplify_ast(ast->right);

  APPLY_RULE(rule_pow_1);
  APPLY_RULE(rule_pow_0);
  APPLY_RULE(rule_mul_0_rhs);
  APPLY_RULE(rule_mul_0_lhs);
  APPLY_RULE(rule_mul_1_rhs);
  APPLY_RULE(rule_mul_1_lhs);
}