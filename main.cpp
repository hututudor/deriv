#include <stdio.h>
#include <stdlib.h>

enum token_type {
  TOKEN_PLUS,
  TOKEN_NUMBER
}

typedef struct {
  token_type type;
  double val;
} token_t;

typedef struct node_t {
  token_t token;
  bool single_child;
  node_t *left, *right;
} node_t;

typedef struct {
  node_t* first;
} ast_t;

int main() {
  token_t* tokens = tokenize_string("x +    23");
  ast_t* ast = simplify_ast(parse_tokens(tokens));

  ast_t* ast = new ast_t;

  ast_t* ast_der = derivate_ast(ast);
  ast_t* simplied_ast = simplify_ast(ast_der);
}

///niste linii de codecvt
//dasa
