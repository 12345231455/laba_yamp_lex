#include <iostream>
#include "LexicalAnalyzer.h"
#include "Token.h"

int main() 
{
    LexicalAnalyzer Analysis("input.txt", "output.txt", "error.txt");
    Analysis.LexAnalize();
}