#pragma once

#include "HashTable.h"
#include "Token.h"

class LexicalAnalyzer 
{
public:
    LexicalAnalyzer(const string& input, const string& output, const string& error)
    {
        in.open(input);
        out.open(output);
        err.open(error);
    };
    ~LexicalAnalyzer()
    {
        if (in.is_open())
        {
            in.close();
        }
        if (out.is_open())
        {
            out.close();
        }
        if (err.is_open())
        {
            err.close();
        }
    };

    void LexAnalize();

private:
    ifstream in;                                 
    ofstream out;                                 
    ofstream err;                                  

    HashTable Table;                                   

    bool OP(char elem) const;                       
    bool DEL(char elem) const;                      
    bool DIG(const string& lexeme);                    
    bool ID_NAME(const string& lexeme) const;    
    bool isKeyword(char elem) const;

    int getKeywordIndex(char elem) const;
   
    Token getNextLexeme();

    Token KeyWord(ifstream& testTxtFile, int num, char c);
    Token processID(char elem);
    Token processNumber(char elem);
    Token processUnknown(char elem);
    Token processChar(char elem);
};
