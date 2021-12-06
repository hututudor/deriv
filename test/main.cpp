#include <stdio.h>

#include "suites/hydrate_ast.h"
#include "suites/load_ast.h"
#include "suites/simplify_ast.h"

int main() {
  suite_load_ast();
  suite_hydrate_ast();
  suite_simplify_ast();
}