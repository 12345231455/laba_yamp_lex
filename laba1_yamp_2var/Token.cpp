#include "Token.h"

using namespace std;

string Token::getType()
{
    string tokenType = "FLAG";

    switch (type) 
    {
    case TokenType::BEGIN:
        tokenType = "BEGIN";
        break;
    case TokenType::END:
        tokenType = "END";
        break;
    case TokenType::DESCRIPTIONS:
        tokenType = "DESCRIPTIONS";
        break;
    case TokenType::DESCR:
        tokenType = "DESCR";
        break;
    case TokenType::OP:
        tokenType = "OP";
        break;
    case TokenType::INT:
        tokenType = "INT";
        break;
    case TokenType::DOUBLE:
        tokenType = "DOUBLE";
        break;
    case TokenType::ITOD:
        tokenType = "ITOD";
        break;
    case TokenType::DTOI:
        tokenType = "DTOI";
        break;
    case TokenType::CONST:
        tokenType = "CONST";
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