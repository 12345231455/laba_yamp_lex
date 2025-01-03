﻿#include <iostream>
#include "LexicalAnalyzer.h"
#include "Node.h"
#include "SemantikAnalyzer.h"
#include "Parser.h"
#include "Token.h"

int main()
{
    LexicalAnalyzer lexer("input.txt", "output.txt", "error.txt");

    Parser parser(lexer);

    Node parseTree = parser.parse();

    SemantikAnalyzer sem;
    sem.sem_parse(parseTree);

    ofstream outTreeFile("ParsingTree.txt");
    parseTree.print(0, outTreeFile);
    outTreeFile.close();
}