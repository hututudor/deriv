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
return func_test_simplify("(2+3)^1-7", "2 + 3 - 7");
TEST_END

TEST_BEGIN(should_simplify_pow_1_complex_deep)
return func_test_simplify("(2+3)^1^1-7", "2 + 3 - 7");
TEST_END

TEST_BEGIN(should_simplify_pow_0_simple)
return func_test_simplify("x^0", "1");
TEST_END

TEST_BEGIN(should_simplify_pow_0_complex)
return func_test_simplify("(2+3)^0+7", "1 + 7");
TEST_END

TEST_BEGIN(should_simplify_pow_0_complex_deep)
return func_test_simplify("(2+3)^x^0+7", "2 + 3 + 7");
TEST_END

SUITE_BEGIN(simplify_ast)
SUITE_ADD(should_simplify_pow_1_simple)
SUITE_ADD(should_simplify_pow_1_complex)
SUITE_ADD(should_simplify_pow_1_complex_deep)
SUITE_ADD(should_simplify_pow_0_simple)
SUITE_ADD(should_simplify_pow_0_complex)
SUITE_ADD(should_simplify_pow_0_complex_deep)
SUITE_END