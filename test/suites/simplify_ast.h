#pragma once

#include "../../src/ast/ast.h"
#include "../../src/ast/simplify.h"
#include "../test_utils.h"

bool func_test_simplify(const char* data, const char* expected = nullptr) {
  char* initial = (char*)malloc(1000);
  strcpy(initial, data);

  node_t* ast = parse_ast_from_string(initial);

  simplify_ast(ast);

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

TEST_BEGIN(should_simplify_pow_1_simple)
return func_test_simplify("x^1", "x");
TEST_END

TEST_BEGIN(should_simplify_pow_1_complex)
return func_test_simplify("(2+3)^1-7", "-2");
TEST_END

TEST_BEGIN(should_simplify_pow_1_complex_deep)
return func_test_simplify("(2+3)^1^1-7", "-2");
TEST_END

TEST_BEGIN(should_simplify_pow_0_simple)
return func_test_simplify("x^0", "1");
TEST_END

TEST_BEGIN(should_simplify_pow_0_complex)
return func_test_simplify("(2+3)^0+7", "8");
TEST_END

TEST_BEGIN(should_simplify_pow_0_complex_deep)
return func_test_simplify("(2+3)^x^0+7", "12");
TEST_END

TEST_BEGIN(should_simplify_mul_0_rhs)
return func_test_simplify("(2 + 5) * 0", "0");
TEST_END

TEST_BEGIN(should_simplify_mul_0_lhs)
return func_test_simplify("0 * (2 + 5)", "0");
TEST_END

TEST_BEGIN(should_simplify_mul_1_rhs)
return func_test_simplify("(2 + 5) * 1", "7");
TEST_END

TEST_BEGIN(should_simplify_mul_1_lhs)
return func_test_simplify("1 * (2 + 5)", "7");
TEST_END

TEST_BEGIN(should_simplify_div_1)
return func_test_simplify("(x + 3) / 1", "x + 3");
TEST_END

TEST_BEGIN(should_simplify_add_0_rhs)
return func_test_simplify("x^5 + 0", "x ^ 5");
TEST_END

TEST_BEGIN(should_simplify_add_0_lhs)
return func_test_simplify("0 + x^5", "x ^ 5");
TEST_END

TEST_BEGIN(should_simplify_sub_0_rhs)
return func_test_simplify("x^5 - 0", "x ^ 5");
TEST_END

TEST_BEGIN(should_simplify_num_add)
return func_test_simplify("4 + 5.2", "9.2");
TEST_END

TEST_BEGIN(should_simplify_num_sub)
return func_test_simplify("4 - 5.2", "-1.2");
TEST_END

TEST_BEGIN(should_simplify_num_mul)
return func_test_simplify("2 * 2", "4");
TEST_END

TEST_BEGIN(should_simplify_num_div)
return func_test_simplify("8 / 4", "2");
TEST_END

TEST_BEGIN(should_simplify_num_pow)
return func_test_simplify("2^3", "8");
TEST_END

TEST_BEGIN(should_simplify_num_sqrt)
return func_test_simplify("sqrt9", "3");
TEST_END

SUITE_BEGIN(simplify_ast)
SUITE_ADD(should_simplify_pow_1_simple)
SUITE_ADD(should_simplify_pow_1_complex)
SUITE_ADD(should_simplify_pow_1_complex_deep)
SUITE_ADD(should_simplify_pow_0_simple)
SUITE_ADD(should_simplify_pow_0_complex)
SUITE_ADD(should_simplify_pow_0_complex_deep)
SUITE_ADD(should_simplify_mul_0_rhs)
SUITE_ADD(should_simplify_mul_0_lhs)
SUITE_ADD(should_simplify_mul_1_rhs)
SUITE_ADD(should_simplify_mul_1_lhs)
SUITE_ADD(should_simplify_div_1)
SUITE_ADD(should_simplify_add_0_rhs)
SUITE_ADD(should_simplify_add_0_lhs)
SUITE_ADD(should_simplify_sub_0_rhs)
SUITE_ADD(should_simplify_num_add)
SUITE_ADD(should_simplify_num_sub)
SUITE_ADD(should_simplify_num_mul)
SUITE_ADD(should_simplify_num_div)
SUITE_ADD(should_simplify_num_pow)
SUITE_ADD(should_simplify_num_sqrt)
SUITE_END