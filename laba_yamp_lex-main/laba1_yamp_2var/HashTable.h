#pragma once
#include "Token.h"

using namespace std;

class HashTable 
{
public:

    HashTable() 
    {
        for (int i = 0; i < Table_Size; ++i)
        {
            Table[i] = nullptr;
        }
    };

    ~HashTable() 
    {
        for (long long i = 0; i < Table_Size; i++)
        {
            delete Table[i];
        }
    };

    void Insert(const Token& token);
    void print(ofstream& outputFile, ofstream& errorFile);

    int Hashing(const string& lexeme) const;
    int tokenCount = 0;

private:
    static const int Table_Size = 10000;
    Token* Table[Table_Size];                  
};
