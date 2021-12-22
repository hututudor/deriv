
#include "ast_gui_utils.h"

#include <queue>
#include <utility>

int ComputeTreeRows(node_t* ast) {
  std::queue<std::pair<node_t*, int>> q;

  q.push({ast, 1});

  int maxHight = 0;

  while (!q.empty()) {
    std::pair<node_t*, int> p = q.front();
    q.pop();

    node_t* node = p.first;
    int depth = p.second;

    if (depth > maxHight) {
      maxHight = depth;
    }

    if (node->left != nullptr) {
      q.push({node->left, depth + 1});
    }

    if (node->right != nullptr) {
      q.push({node->right, depth + 1});
    }
  }

  return maxHight;
}

int ComputeTreeColumns(node_t* ast, int& startingColumn) {
  if (ast == nullptr) {
    return 0;
  }

  int leftColumns = ComputeTreeColumns(ast->left, startingColumn);
  int rightColumns = ComputeTreeColumns(ast->right, startingColumn);

  startingColumn = leftColumns + 1;
  return leftColumns + rightColumns + 1;
}