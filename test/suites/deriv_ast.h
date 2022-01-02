#pragma once

#include "../../src/deriv/global.h"
#include "../test_utils.h"

bool func_test_deriv(const char* data, const char* expected) {
  char* initial = (char*)malloc(1000);
  strcpy(initial, data);

  node_t* ast = parse_ast_from_string(initial);

  Deriva(ast);

  char* expr = convert_ast_to_expression(ast);

  printf(expr);
  ASSERT(strcmp(expected, expr) == 0);

  destroy_ast(ast);
  free(initial);
  free(expr);

  return true;
}

TEST_BEGIN(should_derivate_x)
return func_test_deriv("x", "1");
TEST_END

TEST_BEGIN(should_derivate_add)
return func_test_deriv("x+1", "1");
TEST_END

TEST_BEGIN(should_derivate_diff)
return func_test_deriv("(x^2)-(x^3)", "2 * x ^ 1 * 1 - 3 * x ^ 2 * 1");
TEST_END

TEST_BEGIN(should_derivate_div)
return func_test_deriv("1/x", "1 * x ^ -1");
TEST_END

TEST_BEGIN(should_derivate_mul)
return func_test_deriv("x*x", "1 * x + x * 1");
TEST_END

TEST_BEGIN(should_derivate_pow_x_nr)
return func_test_deriv("x^4", "4 * x ^ 3 * 1");
TEST_END

TEST_BEGIN(should_derivate_pow_nr_x)
return func_test_deriv("4^x", "4 ^ x * ln4");
TEST_END

TEST_BEGIN(should_derivate_pow_expresion_expresion)
return func_test_deriv("(x^2)^(3^x)",
                       "x ^ 2 ^ 3 ^ x * (2 * x ^ 1 * 1 * 3 ^ x / x ^ 2 + 3 ^ x "
                       "* ln3 * ln(x ^ 2))");
TEST_END

TEST_BEGIN(should_derivate_lg)
return func_test_deriv("lgx", "1 / x * ln10");
TEST_END

TEST_BEGIN(should_derivate_ln)
return func_test_deriv("lnx", "x ^ -1");
TEST_END

TEST_BEGIN(should_derivate_sin)
return func_test_deriv("sin x", "cosx * 1");
TEST_END

TEST_BEGIN(should_derivate_cos)
return func_test_deriv("cos x", "(0 - sinx) * 1");
TEST_END

TEST_BEGIN(should_derivate_tan)
return func_test_deriv("tan x", "1 / (cos x) ^ 2 * 1");
TEST_END

TEST_BEGIN(should_derivate_cotan)
return func_test_deriv("cotan(x)", "-1 / sinx ^ 2 * 1");
TEST_END

TEST_BEGIN(should_derivate_sqrt)
return func_test_deriv("sqrt(x)", "1 / 2 * sqrtx * 1");
TEST_END

TEST_BEGIN(should_derivate_arcsin)
return func_test_deriv("arcsin x", "1 / sqrt(1 - x ^ 2) * 1");
TEST_END

TEST_BEGIN(should_derivate_arccos)
return func_test_deriv("arccos x", "-1 / sqrt(1 - x ^ 2) * 1");
TEST_END

TEST_BEGIN(should_derivate_arccotan)
return func_test_deriv("arccotan x", "-1 / (1 + x ^ 2) * 1");
TEST_END

TEST_BEGIN(should_derivate_arctan)
return func_test_deriv("arctan x", "1 / (1 + x ^ 2) * 1");
TEST_END

TEST_BEGIN(should_derivate_error_ln_e)
return func_test_deriv("ln e + ln x", "x ^ -1");
TEST_END

SUITE_BEGIN(deriv_ast)
SUITE_ADD(should_derivate_x)
SUITE_ADD(should_derivate_add)
SUITE_ADD(should_derivate_diff)
SUITE_ADD(should_derivate_div)
SUITE_ADD(should_derivate_mul)
// SUITE_ADD(should_derivate_lg)
// SUITE_ADD(should_derivate_ln)
SUITE_ADD(should_derivate_pow_x_nr)
// SUITE_ADD(should_derivate_pow_nr_x)
// SUITE_ADD(should_derivate_pow_expresion_expresion)
SUITE_ADD(should_derivate_sin)
SUITE_ADD(should_derivate_cos)
// SUITE_ADD(should_derivate_tan)
SUITE_ADD(should_derivate_cotan)
// SUITE_ADD(should_derivate_sqrt)
SUITE_ADD(should_derivate_arcsin)
SUITE_ADD(should_derivate_arccos)
SUITE_ADD(should_derivate_arctan)
SUITE_ADD(should_derivate_arccotan)
// SUITE_ADD(should_derivate_error_ln_e)
SUITE_END