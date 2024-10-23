#include "HashTable.h"
#include <iomanip>

int HashTable::Hashing(const string& lexeme) const
{
    int hash = 0;
    for (char elem : lexeme)
    {
        hash = (hash * 13 + elem) % Table_Size;
    }
    return hash;
}

void HashTable::Insert(const Token& token) 
{
    int hash = Hashing(token.lexeme);
    int originalHash = hash;

    while (Table[hash] != nullptr && Table[hash]->lexeme != token.lexeme)
    {
        hash = (hash + 1) % Table_Size;
    }

    if (Table[hash] == nullptr) 
    {
        Table[hash] = new Token(token.type, token.lexeme, hash);
    }
}

void HashTable::print(ofstream& outputFile, ofstream& errorFile)
{
    for (int i = 0; i < Table_Size; i++)
    {
        if (Table[i]) 
        {
            if (Table[i]->type != TokenType::FLAG && Table[i]->type != TokenType::ERROR)
            {
                outputFile << setw(10) << Table[i]->getType()
                    << setw(10) << " | "
                    << setw(10) << Table[i]->lexeme
                    << setw(10) << " | "
                    << setw(10) << Table[i]->hash << '\n';
            }
        }
    }

    for (int i = 0; i < Table_Size; i++)
    {
        if (Table[i] && Table[i]->type == TokenType::ERROR) 
        {
            errorFile << setw(10) << "ERROR"
                << setw(10) << " | "
                << setw(10) << Table[i]->lexeme
                << setw(10) << " | "
                << setw(10) << Table[i]->hash << '\n';
        }
    }
}
