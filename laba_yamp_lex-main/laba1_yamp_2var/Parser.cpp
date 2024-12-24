#include "Parser.h"

int operatorsCount = 0;
int countLines = 1;
int deskrNodeCount = 1;

void Parser::getNextToken()
{
    currentToken = lexer.getNextLexeme();
    lexer.Table.Insert(currentToken);
    if (currentToken.type == TokenType::ERROR) 
    {
        ofstream out("error.txt", ios::app);
        out << "Lexical error " + currentToken.lexeme + '\n';
        out.close();
        exit(1);
    }
}

Node Parser::parse() 
{
    Node n(" ");
    n.addSon("Begin");
    Program(n.getSon(n.children.size() - 1));

    n.addSon("Descriptions");
    Descriptions(n.getSon(n.children.size() - 1));

    n.addSon("Operators");
    Operators(n.getSon(n.children.size() - 1));

    n.addSon("End");
    End(n.getSon(n.children.size() - 1));

    return n;
}

void Parser::Program(Node& n) 
{
    getNextToken();
    countLines++;
    if (currentToken.type == TokenType::TYPE && currentToken.lexeme == "int") 
    {
        n.addSon(currentToken.lexeme);
        getNextToken();
        if (currentToken.type == TokenType::ID_NAME)
        {
            n.addSon(currentToken.lexeme);

            getNextToken();
            if (currentToken.type == TokenType::DELIMITER)
            {
                n.addSon(currentToken.lexeme);

                getNextToken();
                if (currentToken.type == TokenType::DELIMITER) 
                {
                    n.addSon(currentToken.lexeme);
                    getNextToken();
                    if (currentToken.type == TokenType::DELIMITER) 
                    {
                        n.addSon(currentToken.lexeme);

                        getNextToken();
                    }
                    else
                        Out_Error();
                }
                else
                    Out_Error();
            }
            else
                Out_Error();
        }
        else
            Out_Error();
    }
    else
        Out_Error();
}

void Parser::Descriptions(Node& n)
{
    while (currentToken.type == TokenType::TYPE)
    {
        n.addSon("deskrNode" + to_string(deskrNodeCount));
        deskrNodeCount++;
        Descr(n.getSon(n.children.size() - 1));
    }
}

void Parser::Descr(Node& n) 
{
    if (currentToken.type == TokenType::TYPE)
    {
        n.addSon(currentToken.lexeme);
        countLines++;

        getNextToken();
        if (currentToken.type == TokenType::ID_NAME) 
        {
            n.addSon("VarList");
            VarList(n.getSon(n.children.size() - 1));
            if (currentToken.type == TokenType::DELIMITER) 
            {
                n.addSon(currentToken.lexeme);
                getNextToken();
            }
            else
                Out_Error();
        }
        else
            Out_Error();
    }
    else
        Out_Error();
}

void Parser::VarList(Node& n)
{
    if (currentToken.type == TokenType::ID_NAME)
    {
        n.addSon(currentToken.lexeme);
        getNextToken();

        while (currentToken.type == TokenType::DELIMITER && currentToken.lexeme == ",") 
        {
            getNextToken();
            if (currentToken.type == TokenType::ID_NAME) 
            {
                n.addSon(currentToken.lexeme);
                getNextToken();
            }
            else
                Out_Error();
        }
    }
}

void Parser::Operators(Node& n)
{
    while (currentToken.type == TokenType::ID_NAME) 
    {
        operatorsCount++;
        countLines++;
        n.addSon("OpLine " + to_string(operatorsCount));
        Op(n.getSon(n.children.size() - 1));
    }
}

void Parser::Op(Node& n)
{
    n.addSon(currentToken.lexeme);
    getNextToken();
    if (currentToken.type == TokenType::OP && currentToken.lexeme == "=") 
    {
        n.addSon(currentToken.lexeme);
        getNextToken();
        if (currentToken.type == TokenType::OP)
            Out_Error();
        Expr(n.getSon(n.children.size() - 1));
        if (currentToken.type == TokenType::DELIMITER)
        {
            n.addSon(currentToken.lexeme);
            getNextToken();
        }
        else
            Out_Error();
    }
    else
        Out_Error();
}

void Parser::Expr(Node& n) 
{
    if (currentToken.type == TokenType::FUNC || currentToken.type == TokenType::ID_NAME ||
        currentToken.type == TokenType::INT_CONST || currentToken.type == TokenType::DOUBLE_CONST ||
        currentToken.lexeme == "(") 
    {
        n.addSon("SimpleExpr");
        SimpleExpr(n.getSon(n.children.size() - 1));
    }
    else
        Out_Error();
    if (currentToken.type == TokenType::OP && currentToken.lexeme != "=")
    {
        string operatorLexeme = currentToken.lexeme;
        n.addSon(operatorLexeme);
        getNextToken();
        if (currentToken.type == TokenType::FUNC || currentToken.type == TokenType::ID_NAME ||
            currentToken.type == TokenType::INT_CONST || currentToken.type == TokenType::DOUBLE_CONST ||
            currentToken.lexeme == "(")
            Expr(n.getSon(n.children.size() - 1));
        else
            Out_Error();
    }
}

void Parser::SimpleExpr(Node& n)
{
    if (currentToken.lexeme == "(")
    {
        n.addSon("(");
        getNextToken();
        Expr(n.getSon(n.children.size() - 1));
        if (currentToken.lexeme == ")") 
        {
            n.addSon(")");
            getNextToken();
        }
        else
            Out_Error();
    }
    else if (currentToken.type == TokenType::INT_CONST) 
    {
        n.addSon("INT_CONST");
        n.children[0].addSon(currentToken.lexeme);
        getNextToken();
    }
    else if (currentToken.type == TokenType::DOUBLE_CONST) 
    {
        n.addSon("DOUBLE_CONST");
        n.children[0].addSon(currentToken.lexeme);
        getNextToken();
    }
    else if (currentToken.type == TokenType::ID_NAME)
    {
        n.addSon("ID_NAME");
        n.children[0].addSon(currentToken.lexeme);
        getNextToken();
    }
    else if (currentToken.type == TokenType::FUNC) 
    {
        n.addSon(currentToken.lexeme);
        getNextToken();
        if (currentToken.lexeme == "(")
        {
            n.addSon("(");
            getNextToken();
            Expr(n.getSon(n.children.size() - 1));
            if (currentToken.lexeme == ")")
            {
                n.addSon(")");
                getNextToken();
            }
            else
                Out_Error();
        }
        else
            Out_Error();
    }
    else
        Out_Error();
}

void Parser::End(Node& n)
{
    if (currentToken.type == TokenType::END)
    {
        n.addSon(currentToken.lexeme);
        countLines++;
        getNextToken();
        if (currentToken.type == TokenType::ID_NAME)
        {
            n.addSon(currentToken.lexeme);
            getNextToken();
            if (currentToken.type == TokenType::DELIMITER)
            {
                n.addSon(currentToken.lexeme);
                getNextToken();
                if (currentToken.type == TokenType::DELIMITER)
                {
                    n.addSon(currentToken.lexeme);
                    getNextToken();
                }
                else
                    Out_Error();
            }
            else
                Out_Error();
        }
        else
            Out_Error();
    }
    else
        Out_Error();
}

void Parser::Out_Error()
{
    ofstream out ("error.txt", ios::app);
    out << "Syntax error" + currentToken.lexeme + " in line " + to_string(countLines) + '\n';
    out.close();
    exit (1);
}