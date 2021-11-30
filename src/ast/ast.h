#ifndef AST_H
#define AST_H

enum token_type {
  TOKEN_NUMBER,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_MUL,
  TOKEN_DIV,
  TOKEN_L_PAREN,
  TOKEN_R_PAREN,
  TOKEN_POW,
  TOKEN_SQRT,
  TOKEN_SIN,
  TOKEN_COS,
  TOKEN_TAN,
  TOKEN_COTAN,
  TOKEN_ARCSIN,
  TOKEN_ARCCOS,
  TOKEN_ARCTAN,
  TOKEN_ARCCOTAN,
  TOKEN_LG,
  TOKEN_LN,
  TOKEN_X,
  TOKEN_E,  // implement this
  TOKEN_EOF
};

typedef struct {
  token_type type;
  double val;
} token_t;

typedef struct node_t {
  token_t token;
  node_t *left, *right;

  node_t() {
    this->token.type = TOKEN_EOF;
    this->left = nullptr;
    this->right = nullptr;
  }
} node_t;

node_t* parse_ast_from_string_tudor(char* data);

void print_ast(node_t* ast, int indentation, bool left);

#endif