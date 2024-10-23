#pragma once

#include <string>
#include <fstream>

using namespace std;

enum class TokenType
{     
    BEGIN,
    END,
    DESCRIPTIONS,
    DESCR,
    OP,
    INT,
    DOUBLE,
    ITOD,
    DTOI,
    CONST,
    DELIMITER,
    ID_NAME,
    ERROR,
    FLAG
};

class Token 
{
public:
    TokenType type;
    string lexeme;
    int hash;

    Token() : type(TokenType::FLAG), lexeme(""), hash(0) {}

    Token(TokenType t, const string& lex, int hsh) : type(t), lexeme(lex), hash(hsh) {}

    string getType();
};
