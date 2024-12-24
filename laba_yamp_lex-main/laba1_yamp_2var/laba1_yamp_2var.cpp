#include <iostream>
#include "LexicalAnalyzer.h"
#include "Node.h"
#include "Parser.h"
#include "Token.h"

int main()
{
    LexicalAnalyzer lexer("input.txt", "output.txt", "error.txt");

    Parser parser(lexer);

    Node parseTree = parser.parse();

    ofstream outTreeFile("ParsingTree.txt");
    parseTree.print(0, outTreeFile);
    outTreeFile.close();
}