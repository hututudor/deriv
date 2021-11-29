#include <stdio.h>

#include "ast.h"
#include "ast_node_array.h"
#include "global.h"
#include "io.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Usage: %s <in_file> <out_file>\n", argv[0]);
    return 0;
  }

  char* expression = read_entire_file_tudor(argv[1]);

  printf("%s", expression);

  node_t* ast = parse_ast_from_string_tudor(expression);

  Deriva(ast);

  printf("\nDERIV: \n");
  print_ast(ast, 0, false);

  // ast_t* ast = simplify_ast(parse_tokens(tokens));

  // ast_t* ast = new ast_t;

  // ast_t* ast_der = derivate_ast(ast);
  // ast_t* simplied_ast = simplify_ast(ast_der);
}
