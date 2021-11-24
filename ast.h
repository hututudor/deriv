#ifndef AST_H
#define AST_H

enum token_type { TOKEN_NUMER, TOKEN_PLUS, TOKEN_MINUS, TOKEN_POW };

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

ast_t* parse_ast_from_string_tudor(char* data);

#endif