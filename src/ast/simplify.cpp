#include "simplify.h"

#include <math.h>
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

bool rule_div_1(node_t*& ast) {
  if (!(ast->token.type == TOKEN_DIV && ast->right &&
        ast->right->token.type == TOKEN_NUMBER && ast->right->token.val == 1)) {
    return false;
  }

  node_t* left = clone_ast(ast->left);

  destroy_ast(ast);

  ast = left;

  return true;
}

bool rule_add_0_rhs(node_t*& ast) {
  if (!(ast->token.type == TOKEN_PLUS && ast->right &&
        ast->right->token.type == TOKEN_NUMBER && ast->right->token.val == 0)) {
    return false;
  }

  node_t* left = clone_ast(ast->left);

  destroy_ast(ast);

  ast = left;

  return true;
}

bool rule_add_0_lhs(node_t*& ast) {
  if (!(ast->token.type == TOKEN_PLUS && ast->left &&
        ast->left->token.type == TOKEN_NUMBER && ast->left->token.val == 0)) {
    return false;
  }

  node_t* right = clone_ast(ast->right);

  destroy_ast(ast);

  ast = right;

  return true;
}

bool rule_sub_0_rhs(node_t*& ast) {
  if (!(ast->token.type == TOKEN_MINUS && ast->right &&
        ast->right->token.type == TOKEN_NUMBER && ast->right->token.val == 0)) {
    return false;
  }

  node_t* left = clone_ast(ast->left);

  destroy_ast(ast);

  ast = left;

  return true;
}

bool rule_num_add(node_t*& ast) {
  if (!(ast->token.type == TOKEN_PLUS && ast->left &&
        ast->left->token.type == TOKEN_NUMBER && ast->right &&
        ast->right->token.type == TOKEN_NUMBER)) {
    return false;
  }

  double val = ast->left->token.val + ast->right->token.val;

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_NUMBER;
  ast->token.val = val;

  ast->left = nullptr;
  ast->right = nullptr;

  return true;
}

bool rule_num_sub(node_t*& ast) {
  if (!(ast->token.type == TOKEN_MINUS && ast->left &&
        ast->left->token.type == TOKEN_NUMBER && ast->right &&
        ast->right->token.type == TOKEN_NUMBER)) {
    return false;
  }

  double val = ast->left->token.val - ast->right->token.val;

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_NUMBER;
  ast->token.val = val;

  ast->left = nullptr;
  ast->right = nullptr;

  return true;
}

bool rule_num_mul(node_t*& ast) {
  if (!(ast->token.type == TOKEN_MUL && ast->left &&
        ast->left->token.type == TOKEN_NUMBER && ast->right &&
        ast->right->token.type == TOKEN_NUMBER)) {
    return false;
  }

  double val = ast->left->token.val * ast->right->token.val;

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_NUMBER;
  ast->token.val = val;

  ast->left = nullptr;
  ast->right = nullptr;

  return true;
}

bool rule_num_div(node_t*& ast) {
  if (!(ast->token.type == TOKEN_DIV && ast->left &&
        ast->left->token.type == TOKEN_NUMBER && ast->right &&
        ast->right->token.type == TOKEN_NUMBER)) {
    return false;
  }

  double val = ast->left->token.val / ast->right->token.val;

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_NUMBER;
  ast->token.val = val;

  ast->left = nullptr;
  ast->right = nullptr;

  return true;
}

bool rule_num_pow(node_t*& ast) {
  if (!(ast->token.type == TOKEN_POW && ast->left &&
        ast->left->token.type == TOKEN_NUMBER && ast->right &&
        ast->right->token.type == TOKEN_NUMBER)) {
    return false;
  }

  double val = pow(ast->left->token.val, ast->right->token.val);

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_NUMBER;
  ast->token.val = val;

  ast->left = nullptr;
  ast->right = nullptr;

  return true;
}

bool rule_num_sqrt(node_t*& ast) {
  if (!(ast->token.type == TOKEN_SQRT && ast->left &&
        ast->left->token.type == TOKEN_NUMBER)) {
    return false;
  }

  double val = sqrt(ast->left->token.val);

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_NUMBER;
  ast->token.val = val;

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
  APPLY_RULE(rule_mul_0_rhs);
  APPLY_RULE(rule_mul_0_lhs);
  APPLY_RULE(rule_mul_1_rhs);
  APPLY_RULE(rule_mul_1_lhs);
  APPLY_RULE(rule_div_1);
  APPLY_RULE(rule_add_0_rhs);
  APPLY_RULE(rule_add_0_lhs);
  APPLY_RULE(rule_sub_0_rhs);
  APPLY_RULE(rule_num_add);
  APPLY_RULE(rule_num_sub);
  APPLY_RULE(rule_num_mul);
  APPLY_RULE(rule_num_div);
  APPLY_RULE(rule_num_pow);
  APPLY_RULE(rule_num_sqrt);
}