#include <iostream>
#include <queue>

#include "derivaMultiplication.h"
#include "derivaPow.h"

using namespace std;

void Deriva(node_t*& start) {
  switch (start->token.type) {
    case TOKEN_NUMBER:
      return;
      break;
    case TOKEN_X:
      return;
      break;
    case TOKEN_E:
      return;
      break;
    // case TOKEN_PLUS:
    // case TOKEN_MINUS:
    //         return DerivaSum(start);
    //         break;
    case TOKEN_MUL:
      return DerivaMultiplication(start);
      break;
    // case TOKEN_DIV:
    //         return DerivaDivide(start);
    //         break;
    case TOKEN_POW:
      return DerivaPow(start);
      break;
      // case TOKEN_LN:
      //         return DerivaLn(start);
      //         break;
      // case TOKEN_LG:
      // case TOKEN_LOG:
      //         return DerivaLog(start);
      //         break;
      // case TOKEN_COS:
      //         return DerivaCos(start);
      //         break;
      // case TOKEN_SIN:
      //         return DerivaSin(start);
      //         break;
      // case TOKEN_TAN:
      //         return DerivaTan(start);
      //         break;
      // case TOKEN_COTAN:
      //         return DerivaCotan(start);
      //         break;
      // case TOKEN_SQRT:
      //         return DerivaSqrt(start);
      //         break;
      // case TOKEN_ARCSIN:
      //         return DerivaArcSin(start);
      //         break;
      // case TOKEN_ARCCOS:
      //         return DerivaArcCos(start);
      //         break;
      //         ;
      // case TOKEN_ARCCOTAN:
      //         return DerivaArcCotan(start);
      //         break;
      // case TOKEN_ARCTAN:
      //         return DerivaArcTan(start);
      //         break;

    default:
      return;
      break;
  }
}

bool isNumber(token_type token) {
  if (token == TOKEN_E || token == TOKEN_NUMBER) {
    return true;
  } else {
    return false;
  }
}

void CopySubTree(node_t* from, node_t*& to) {
  to->token.type = from->token.type;
  to->token.val = from->token.val;

  queue<node_t*> bfsFrom;
  bfsFrom.push(from);

  queue<node_t*> bfsTo;
  bfsTo.push(to);

  while (!bfsFrom.empty()) {
    node_t* actualFrom = bfsFrom.front();
    bfsFrom.pop();

    node_t* actualTo = bfsTo.front();
    bfsTo.pop();

    if (from->left != NULL) {
      bfsFrom.push(from->left);

      node_t* newLeft = new node_t();
      newLeft->token.type = from->left->token.type;
      newLeft->token.val = from->left->token.val;

      actualTo->left = newLeft;
      bfsTo.push(newLeft);
    }
    if (from->right != NULL) {
      bfsFrom.push(from->right);

      node_t* newRight = new node_t();
      newRight->token.type = from->right->token.type;
      newRight->token.val = from->right->token.val;

      actualTo->right = newRight;
      bfsTo.push(newRight);
    }
  }
}
