#pragma once

#include "../../src/deriv/global.h"
#include "../test_utils.h"

bool func_test_deriv(const char* data, const char* expected) {
  char* initial = (char*)malloc(1000);
  strcpy(initial, data);

  node_t* ast = parse_ast_from_string(initial);

  Deriva(ast);

  char* expr = convert_ast_to_expression(ast);

  ASSERT(strcmp(expected, expr) == 0);

  destroy_ast(ast);
  free(initial);
  free(expr);

  return true;
}

TEST_BEGIN(should_derivate_add)
return func_test_deriv("x-1", "1");
TEST_END

SUITE_BEGIN(deriv_ast)
SUITE_ADD(should_derivate_add)
SUITE_END