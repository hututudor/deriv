#include <stdio.h>
#include <stdlib.h>

#include "ast/ast.h"
#include "ast/simplify.h"
#include "deriv/global.h"
#include "utils/ast_node_array.h"
#include "utils/io.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Usage: %s <in_file> <out_file>\n", argv[0]);
    return 0;
  }

  char* expression = read_entire_file(argv[1]);

  node_t* ast = parse_ast_from_string(expression);

  simplify_ast(ast);
  Deriva(ast);
  simplify_ast(ast);

  char* expr = convert_ast_to_expression(ast);
  destroy_ast(ast);

  write_entire_file(argv[2], expr);
  free(expr);
  free(expression);
}
