#include <iostream>
#include <queue>

#include "../ast/ast.h"
#include "derivaArccos.h"
#include "derivaArccotan.h"
#include "derivaArcsin.h"
#include "derivaArctan.h"
#include "derivaCos.h"
#include "derivaCotan.h"
#include "derivaDIV.h"
#include "derivaLG.h"
#include "derivaLN.h"
#include "derivaMultiplication.h"
#include "derivaNumber.h"
#include "derivaPow.h"
#include "derivaSin.h"
#include "derivaSqrt.h"
#include "derivaSumORDiff.h"
#include "derivaTan.h"
#include "derivaX.h"

using namespace std;

void Deriva(node_t*& start) {
  switch (start->token.type) {
    case TOKEN_E:
    case TOKEN_NUMBER:
      return DerivaNumber(start);
    case TOKEN_X:
      return DerivaX(start);
    case TOKEN_PLUS:
    case TOKEN_MINUS:
      return DerivaSumOrDiff(start);
    case TOKEN_MUL:
      return DerivaMultiplication(start);
    case TOKEN_DIV:
      return DerivaDIV(start);
    case TOKEN_POW:
      return DerivaPow(start);
    case TOKEN_LN:
      return DerivaLN(start);
    case TOKEN_LG:
      return DerivaLG(start);
      // case TOKEN_LOG:
      //         return DerivaLog(start);
    case TOKEN_COS:
      return DerivaCos(start);
    case TOKEN_SIN:
      return DerivaSin(start);
    case TOKEN_TAN:
      return DerivaTan(start);
    case TOKEN_COTAN:
      return DerivaCotan(start);
    case TOKEN_SQRT:
      return DerivaSqrt(start);
    case TOKEN_ARCSIN:
      return DerivaArcsin(start);
    case TOKEN_ARCCOS:
      return DerivaArccos(start);
    case TOKEN_ARCCOTAN:
      return DerivaArccotan(start);
    case TOKEN_ARCTAN:
      return DerivaArctan(start);

    default:
      return;
  }
}

bool isNumber(token_type token) {
  if (token == TOKEN_E || token == TOKEN_NUMBER) {
    return true;
  } else {
    return false;
  }
}

void CopySubTree(node_t* from, node_t*& to) { to = clone_ast(from); }
