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

bool rule_ln_e(node_t*& ast) {
  if (!(ast->token.type == TOKEN_LN && ast->left &&
        ast->left->token.type == TOKEN_E)) {
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

bool rule_lg_10(node_t*& ast) {
  if (!(ast->token.type == TOKEN_LG && ast->left &&
        ast->left->token.type == TOKEN_NUMBER && ast->left->token.val == 10)) {
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

bool rule_x_pow_nr_MUL_x_pow_nr(node_t*& ast) {
  if (!(ast->token.type == TOKEN_MUL && ast->left && ast->right &&
        ast->left->token.type == TOKEN_POW &&
        ast->right->token.type == TOKEN_POW && ast->left->left &&
        ast->left->right && ast->right->left && ast->right->right &&
        ast->left->left->token.type == TOKEN_X &&
        ast->left->right->token.type == TOKEN_NUMBER &&
        ast->right->left->token.type == TOKEN_X &&
        ast->right->right->token.type == TOKEN_NUMBER)) {
    return false;
  }

  double pow_1 = ast->left->right->token.val;
  double pow_2 = ast->right->right->token.val;

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_POW;

  ast->left = new node_t();
  ast->left->token.type = TOKEN_X;

  ast->right = new node_t();
  ast->right->token.type = TOKEN_NUMBER;
  ast->right->token.val = pow_1 + pow_2;
  return true;
}

bool rule_x_pow_nr_DIV_x_pow_nr(node_t*& ast) {
  if (!(ast->token.type == TOKEN_DIV && ast->left && ast->right &&
        ast->left->token.type == TOKEN_POW &&
        ast->right->token.type == TOKEN_POW && ast->left->left &&
        ast->left->right && ast->right->left && ast->right->right &&
        ast->left->left->token.type == TOKEN_X &&
        ast->left->right->token.type == TOKEN_NUMBER &&
        ast->right->left->token.type == TOKEN_X &&
        ast->right->right->token.type == TOKEN_NUMBER)) {
    return false;
  }

  double pow_1 = ast->left->right->token.val;
  double pow_2 = ast->right->right->token.val;

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_POW;

  ast->left = new node_t();
  ast->left->token.type = TOKEN_X;

  ast->right = new node_t();
  ast->right->token.type = TOKEN_NUMBER;
  ast->right->token.val = pow_1 - pow_2;
  return true;
}

bool rule_nr_pow_x_DIV_nr_pow_x(node_t*& ast) {
  if (!(ast->token.type == TOKEN_DIV && ast->left && ast->right &&
        ast->left->token.type == TOKEN_POW &&
        ast->right->token.type == TOKEN_POW && ast->left->left &&
        ast->left->right && ast->right->left && ast->right->right &&
        ast->left->left->token.type == TOKEN_NUMBER &&
        ast->left->right->token.type == TOKEN_X &&
        ast->right->left->token.type == TOKEN_NUMBER &&
        ast->right->right->token.type == TOKEN_X)) {
    return false;
  }

  double base_1 = ast->left->left->token.val;
  double base_2 = ast->right->left->token.val;

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_POW;

  ast->left = new node_t();
  ast->left->token.type = TOKEN_NUMBER;
  ast->left->token.val = base_1 / base_2;

  ast->right = new node_t();
  ast->right->token.type = TOKEN_X;
  return true;
}

bool rule_nr_pow_x_MUL_nr_pow_x(node_t*& ast) {
  if (!(ast->token.type == TOKEN_MUL && ast->left && ast->right &&
        ast->left->token.type == TOKEN_POW &&
        ast->right->token.type == TOKEN_POW && ast->left->left &&
        ast->left->right && ast->right->left && ast->right->right &&
        ast->left->left->token.type == TOKEN_NUMBER &&
        ast->left->right->token.type == TOKEN_X &&
        ast->right->left->token.type == TOKEN_NUMBER &&
        ast->right->right->token.type == TOKEN_X)) {
    return false;
  }

  double base_1 = ast->left->left->token.val;
  double base_2 = ast->right->left->token.val;

  destroy_ast(ast);

  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_POW;

  ast->left = new node_t();
  ast->left->token.type = TOKEN_NUMBER;
  ast->left->token.val = base_1 * base_2;

  ast->right = new node_t();
  ast->right->token.type = TOKEN_X;

  return true;
}

bool rule_x_add_x(node_t*& ast) {
  if (!(ast->token.type == TOKEN_PLUS && ast->left && ast->right &&
        ast->left->token.type == TOKEN_X &&
        ast->right->token.type == TOKEN_X)) {
    return false;
  }

  destroy_ast(ast);
  ast = (node_t*)malloc(sizeof(node_t));
  ast->token.type = TOKEN_MUL;

  ast->left = new node_t();
  ast->left->token.type = TOKEN_NUMBER;
  ast->left->token.val = 2;

  ast->right = new node_t();
  ast->right->token.type = TOKEN_X;

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
  APPLY_RULE(rule_ln_e);
  APPLY_RULE(rule_lg_10);
  APPLY_RULE(rule_x_pow_nr_MUL_x_pow_nr);
  APPLY_RULE(rule_x_pow_nr_DIV_x_pow_nr);
  APPLY_RULE(rule_nr_pow_x_MUL_nr_pow_x);
  APPLY_RULE(rule_nr_pow_x_DIV_nr_pow_x);
  APPLY_RULE(rule_x_add_x);
}