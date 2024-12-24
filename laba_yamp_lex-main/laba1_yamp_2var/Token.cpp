#include "Token.h"

using namespace std;

string Token::getType()
{
    string tokenType = "FLAG";

    switch (type) 
    {
    case TokenType::END:
        tokenType = "END";
        break;
    case TokenType::OP:
        tokenType = "OP";
        break;
    case TokenType::TYPE:
        tokenType = "TYPE";
        break;
    case TokenType::FUNC:
        tokenType = "FUNC";
        break;
    case TokenType::INT_CONST:
        tokenType = "INT_CONST";
        break;
    case TokenType::DOUBLE_CONST:
        tokenType = "DOUBLE_CONST";
        break;
    case TokenType::DELIMITER:
        tokenType = "DELIMITER";
        break;
    case TokenType::ID_NAME:
        tokenType = "ID_NAME";
        break;
    case TokenType::ERROR:
        tokenType = "ERROR";
        break;
    default:
        tokenType = "FLAG";
        break;
    }

    return tokenType;
}