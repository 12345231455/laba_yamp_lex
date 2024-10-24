#include "LexicalAnalyzer.h"
#include "Token.h"
#include <iostream>
#include <vector>

using namespace std;

vector<string> words = { "int", "itod", "double",  "dtoi", "return" };

bool LexicalAnalyzer::DIG(const string& lexeme) 
{
    for (char c : lexeme)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}


bool LexicalAnalyzer::ID_NAME(const string& lexeme) const
{
    int count = 0;
    for (const auto elem : lexeme)
    {
        if (!isalpha(elem) && count == 0)
        {
            return false;
        }
        else if (!isalnum(elem) && !isalpha(elem))
        {
            return false;
        }
        count++;
    }
    
    return true;
}


bool LexicalAnalyzer::OP(char elem) const
{
    return (elem == '+' || elem == '-' || elem == '=');
}

bool LexicalAnalyzer::DEL(char elem) const
{
    return (elem == '(' || elem == ')' || elem == ',' || elem == ';' || elem == '{' || elem == '}');
}


Token LexicalAnalyzer::KeyWord(ifstream& in, int num, char elem)
{
    string lexeme;
    int count_word_letters = 1;
    int count_all_letters = 1;
    bool flag = false;
    bool flag_to = false;

    lexeme += elem;
    while (in.get(elem) && !isspace(elem))
    {
        if (DEL(elem))
        {
            in.unget();
            break;
        }

        lexeme += elem;

        if (count_all_letters < words[num].size())
        {
            if (elem == words[num][count_all_letters])
            {
                count_word_letters++;
            }
            else if (num != words.size() - 1)
            {
                num++;
                if (elem == words[num][count_all_letters])
               count_word_letters++;
                flag_to = true;
            }
            else
            {
                flag = true;
            }
        }
        else
        {
            flag = true;
        }
        count_all_letters++;
    }

    if (count_word_letters == count_all_letters && (!flag))
    {
        if (num == 0)
        {
            return Token(TokenType::INT, lexeme, 0);
        }
        else if (num == 1 && flag_to)
        {
            return Token(TokenType::ITOD, lexeme, 0);
        }
        else if (num == 2)
        {
            return Token(TokenType::DOUBLE, lexeme, 0);
        }
        else if (num == 3 && flag_to)
        {
            return Token(TokenType::DTOI, lexeme, 0);
        }
        else
        {
            return Token(TokenType::END, lexeme, 0);
        }
    }
    else
    {
        if (!ID_NAME(lexeme))
        {
            return Token(TokenType::ERROR, lexeme, 0);
        }
        else
        {
            return Token(TokenType::ID_NAME, lexeme, 0);
        }
    }
}

Token LexicalAnalyzer::getNextLexeme() 
{
    char elem;

    while (in.get(elem))
    {
        if (isspace(elem)) 
        {
            continue;
        }

        Token token = processChar(elem);
        if (token.type != TokenType::FLAG) 
        {
            return token;
        }
    }

    return Token(TokenType::FLAG, "", 0);
}

Token LexicalAnalyzer::processChar(char elem) 
{
    if (isKeyword(elem))
    {
        return KeyWord(in, getKeywordIndex(elem), elem);
    }

    else if (isalpha(elem))
    {
        return processID(elem);
    }

    else if (isdigit(elem))
    {
        return processNumber(elem);
    }

    else if (OP(elem))
    {
        return Token(TokenType::OP, string(1, elem), 0);
    }

    else if (DEL(elem)) 
    {
        return Token(TokenType::DELIMITER, string(1, elem), 0);
    }

    return processUnknown(elem);
}

bool LexicalAnalyzer::isKeyword(char elem) const 
{
    return elem == 'i' || elem == 'd' || elem == 'r';
}

int LexicalAnalyzer::getKeywordIndex(char elem) const 
{
    switch (elem) 
    {
    case 'i': 
        return 0;
    case 'd': 
        return 2;
    case 'r':
        return 4;
    default: 
        return -1; 
    }
}

Token LexicalAnalyzer::processID(char elem) 
{
    string lexeme(1, elem);

    while (in.get(elem) && isalnum(elem)) 
    {
        lexeme += elem;
    }
    in.unget();

    return Token(TokenType::ID_NAME, lexeme, 0);
}

Token LexicalAnalyzer::processNumber(char elem)
{
    string lexeme(1, elem);
    bool flag_abc = false;

    while (in.get(elem) && !isspace(elem) && !DEL(elem))
    {
        if (isalpha(elem)) 
        {
            flag_abc = true;
        }
        lexeme += elem;
    }
    in.unget();

    return flag_abc ? Token(TokenType::ERROR, lexeme, 0) : Token(TokenType::CONST, lexeme, 0);
}

Token LexicalAnalyzer::processUnknown(char elem)
{
    string lexeme(1, elem);

    while (in.get(elem) && !isspace(elem) && !DEL(elem))
    {
        lexeme += elem;
    }
    in.unget();

    return Token(TokenType::ERROR, lexeme, 0);
}

void LexicalAnalyzer::LexAnalize()
{
    Token token;
    while ((token = getNextLexeme()).type != TokenType::FLAG)
    {
        Table.Insert(token);
    }

    Table.print(out, err);
}