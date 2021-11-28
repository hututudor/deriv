#include "derivaMultiplication.h"
#include "derivaPow.h"


#include <iostream>
using namespace std;

void Deriva(node_t *&start)
{
    cout << start->token.type << '\n';
        switch (start->token.type)
        {
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

bool isNumber(token_type token)
{
    if (token == TOKEN_E || token == TOKEN_NUMBER)
    {
        return true;
    }
    else
    {
        return false;
    }
}

token_type GetTokenType(int token)
{
    switch (token)
    {
    case 1:
        return TOKEN_NUMBER;
        break;
    case 2:
        return TOKEN_X;
        break;
    case 3:
        return TOKEN_PLUS;
        break;
    case 4:
        return TOKEN_MINUS;
        break;
    case 5:
        return TOKEN_MUL;
        break;
    case 6:
        return TOKEN_DIV;
        break;
    case 7:
        return TOKEN_POW;
        break;
    case 8:
        return TOKEN_LN;
        break;
    case 9:
        return TOKEN_LG;
        break;
    case 10:
        return TOKEN_LOG;
        break;
    case 11:
        return TOKEN_COS;
        break;
    case 12:
        return TOKEN_SIN;
        break;
    case 13:
        return TOKEN_TAN;
        break;
    case 14:
        return TOKEN_COTAN;
        break;
    case 15:
        return TOKEN_E;
        break;
    case 16:
        return TOKEN_SQRT;
        break;
    case 17:
        return TOKEN_ARCSIN;
        break;
    case 18:
        return TOKEN_ARCCOS;
        break;
    case 19:
        return TOKEN_ARCCOTAN;
        break;
    case 20:
        return TOKEN_ARCTAN;
        break;

    default:
        return TOKEN_0;
        break;
    }
}