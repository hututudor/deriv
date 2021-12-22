#pragma once

#include "../../src/ast/ast.h"
#include "../test_utils.h"

bool func_test_load(const char* data, const char* expected = nullptr) {
  char* initial = (char*)malloc(1000);
  strcpy(initial, data);

  node_t* ast = parse_ast_from_string(initial);
  char* expr = convert_ast_to_expression(ast);

  if (expected) {
    ASSERT(strcmp(expected, expr) == 0);
  } else {
    ASSERT(strcmp(initial, expr) == 0);
  }

  destroy_ast(ast);
  free(initial);
  free(expr);

  return true;
}

TEST_BEGIN(should_load_a_simple_expression)
return func_test_load("1 + 2");
TEST_END

TEST_BEGIN(should_consider_mul_and_div_precendece)
return func_test_load("1 / (x * 2)", "1 / (x * 2)");
TEST_END

TEST_BEGIN(should_consider_mul_precendece_no_parans)
return func_test_load("5 * (6 * 7)", "5 * 6 * 7");
TEST_END

TEST_BEGIN(should_consider_div_precendece_with_parans)
return func_test_load("5 / (6 / 7)", "5 / (6 / 7)");
TEST_END

TEST_BEGIN(should_consider_div_precendece_no_parans)
return func_test_load("5 / 6 / 7", "5 / 6 / 7");
TEST_END

TEST_BEGIN(should_consider_add_and_sub_precendece)
return func_test_load("1 - (x + 2)", "1 - (x + 2)");
TEST_END

TEST_BEGIN(should_consider_sub_precendece_no_parans)
return func_test_load("5 - (6 - 7)", "5 - (6 - 7)");
TEST_END

TEST_BEGIN(should_consider_add_precendece_no_parans)
return func_test_load("5 + (6 + 7)", "5 + 6 + 7");
TEST_END

TEST_BEGIN(should_consider_pow_precendece_no_parans)
return func_test_load("5 ^ 6 ^ 7", "5 ^ 6 ^ 7");
TEST_END

TEST_BEGIN(should_consider_pow_precendece_with_parans)
return func_test_load("(5 ^ 6) ^ 7", "(5 ^ 6) ^ 7");
TEST_END

TEST_BEGIN(should_load_a_complex_expression)
return func_test_load("cotan(6/4) * sin30+cos0.5-sqrtx + 3 * (2 - 3)",
                      "cotan(6 / 4) * sin30 + cos0.5 - sqrtx + 3 * (2 - 3)");
TEST_END

SUITE_BEGIN(load_ast)
SUITE_ADD(should_load_a_simple_expression)
SUITE_ADD(should_consider_mul_and_div_precendece)
SUITE_ADD(should_consider_mul_precendece_no_parans)
SUITE_ADD(should_consider_div_precendece_with_parans)
SUITE_ADD(should_consider_div_precendece_no_parans)
SUITE_ADD(should_consider_add_and_sub_precendece)
SUITE_ADD(should_consider_sub_precendece_no_parans)
SUITE_ADD(should_consider_add_precendece_no_parans)
SUITE_ADD(should_consider_pow_precendece_no_parans)
SUITE_ADD(should_consider_pow_precendece_with_parans)
SUITE_ADD(should_load_a_complex_expression)
SUITE_END