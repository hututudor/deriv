#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "io.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Usage: %s <in_file> <out_file>\n", argv[0]);
    return 0;
  }

  char* expression = read_entire_file_tudor(argv[1]);

  printf("%s", expression);

  parse_ast_from_string_tudor(expression);

  // token_t* tokens = tokenize_string("x +    23");
  // ast_t* ast = simplify_ast(parse_tokens(tokens));

  // ast_t* ast = new ast_t;

  // ast_t* ast_der = derivate_ast(ast);
  // ast_t* simplied_ast = simplify_ast(ast_der);
}