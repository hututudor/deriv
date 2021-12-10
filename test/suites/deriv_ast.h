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

TEST_BEGIN(should_derivate_add)
return func_test_deriv("x-1", "1");
TEST_END

TEST_BEGIN(should_derivate_pow)
return func_test_deriv("x^4", "4 * x ^ 3 * 1");
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

SUITE_BEGIN(deriv_ast)
SUITE_ADD(should_derivate_add)
SUITE_ADD(should_derivate_pow)
SUITE_ADD(should_derivate_cos)
SUITE_ADD(should_derivate_tan)
SUITE_ADD(should_derivate_cotan)
SUITE_ADD(should_derivate_sqrt)
SUITE_ADD(should_derivate_arcsin)
SUITE_END