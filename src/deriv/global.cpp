#include <iostream>
#include <queue>

#include "derivaDIV.h"
#include "derivaMultiplication.h"
#include "derivaNumber.h"
#include "derivaPow.h"
#include "derivaSumORDiff.h"
#include "derivaX.h"

using namespace std;

void Deriva(node_t*& start) {
  switch (start->token.type) {
    case TOKEN_NUMBER:
      return DerivaNumber(start);
      break;
    case TOKEN_X:
      return DerivaX(start);
      break;
    case TOKEN_E:
      return;
      break;
    case TOKEN_PLUS:
    case TOKEN_MINUS:
      return DerivaSumOrDiff(start);
      break;
    case TOKEN_MUL:
      return DerivaMultiplication(start);
      break;
    case TOKEN_DIV:
      return DerivaDIV(start);
      break;
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

    if (from->left != nullptr) {
      bfsFrom.push(from->left);

      node_t* newLeft = new node_t();
      newLeft->token.type = from->left->token.type;
      newLeft->token.val = from->left->token.val;

      actualTo->left = newLeft;
      bfsTo.push(newLeft);
    }
    if (from->right != nullptr) {
      bfsFrom.push(from->right);

      node_t* newRight = new node_t();
      newRight->token.type = from->right->token.type;
      newRight->token.val = from->right->token.val;

      actualTo->right = newRight;
      bfsTo.push(newRight);
    }
  }
}
