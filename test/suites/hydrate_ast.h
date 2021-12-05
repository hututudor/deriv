#pragma once

#include "../../src/ast/ast.h"
#include "../test_utils.h"

bool func_test_hydrate_ast(const char* data, const char* expected = nullptr) {
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

TEST_BEGIN(should_hydrate_a_simple_multiplication)
return func_test_hydrate_ast("3x", "3 * x");
TEST_END

TEST_BEGIN(should_hydrate_a_simple_multiplication_with_funcs)
return func_test_hydrate_ast("3sinx", "3 * sinx");
TEST_END

TEST_BEGIN(should_hydrate_a_simple_multiplication_with_e)
return func_test_hydrate_ast("3sinx", "3 * sinx");
TEST_END

TEST_BEGIN(should_hydrate_a_multiplication_inside_a_func)
return func_test_hydrate_ast("3sin2x+5", "3 * sin(2 * x) + 5");
TEST_END

TEST_BEGIN(should_hydrate_an_unary_minus_at_start)
return func_test_hydrate_ast("-2", "0 - 2");
TEST_END

TEST_BEGIN(should_hydrate_an_unary_plus_at_start)
return func_test_hydrate_ast("+2", "0 + 2");
TEST_END

TEST_BEGIN(should_hydrate_an_unary_minus_in_parens)
return func_test_hydrate_ast("3 * (-2)", "3 * (0 - 2)");
TEST_END

TEST_BEGIN(should_hydrate_an_unary_plus_in_parens)
return func_test_hydrate_ast("3 * (+2)", "3 * (0 + 2)");
TEST_END

TEST_BEGIN(should_hydrate_an_unary_minus_with_funcs)
return func_test_hydrate_ast("-sinx", "0 - sinx");
TEST_END

TEST_BEGIN(should_hydrate_an_unary_minus_with_funcs_before)
return func_test_hydrate_ast("cosx-sinx", "cosx - sinx");
TEST_END

TEST_BEGIN(should_hydrate_an_unary_minus_with_parens_before)
return func_test_hydrate_ast("(2+3)-sinx", "2 + 3 - sinx");
TEST_END

TEST_BEGIN(should_hydrate_an_unary_minus_with_plus)
return func_test_hydrate_ast("1 + -2", "1 - 2");
TEST_END

TEST_BEGIN(should_hydrate_an_unary_plus_with_minus)
return func_test_hydrate_ast("1 - +2", "1 - 2");
TEST_END

TEST_BEGIN(should_hydrate_a_complex_expression)
return func_test_hydrate_ast("2 + 3x - 5sin(x) + 5(2 - 3) -2e",
                             "2 + 3 * x - 5 * sinx + 5 * (2 - 3) - 2 * e");
TEST_END

SUITE_BEGIN(hydrate_ast)
SUITE_ADD(should_hydrate_a_simple_multiplication)
SUITE_ADD(should_hydrate_a_simple_multiplication_with_funcs)
SUITE_ADD(should_hydrate_a_simple_multiplication_with_e)
SUITE_ADD(should_hydrate_a_multiplication_inside_a_func)
SUITE_ADD(should_hydrate_an_unary_minus_at_start)
SUITE_ADD(should_hydrate_an_unary_plus_at_start)
SUITE_ADD(should_hydrate_an_unary_minus_in_parens)
SUITE_ADD(should_hydrate_an_unary_plus_in_parens)
SUITE_ADD(should_hydrate_an_unary_minus_with_funcs)
SUITE_ADD(should_hydrate_an_unary_minus_with_funcs_before)
SUITE_ADD(should_hydrate_an_unary_minus_with_parens_before)
SUITE_ADD(should_hydrate_an_unary_minus_with_plus)
SUITE_ADD(should_hydrate_an_unary_plus_with_minus)
SUITE_ADD(should_hydrate_a_complex_expression)
SUITE_END