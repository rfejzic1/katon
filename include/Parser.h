#pragma once

// ToDo Abstract Syntax Tree
//  - Literal nodes
//  - Expression nodes
//  - Statement nodes
//  - Nodes for control statements and code blocks
//  - Should the tree be a binary tree???
//  - Operator precedence, left and right association
//  - Symbol table

#include <string>
#include <vector>

#include "AbstractSyntaxTree/AbstractSyntaxTree.h"
#include "Klex.h"

class Parser {
    std::string filepath;
    Klex* klex;
    AbstractSyntaxTree* astree;

    void openKlex();
    void checkKlex();
    void closeKlex();

    Token get();
    void consume(TokenType tokenType);
    void error(const char* message);
    void log(const char* message);

    void object();
    void attributeDecl();
    void method();
    void statementBlock();
    void statement();
    void ifStatement();
    void whileStatement();
    void forStatement();
    void tryCatchStatement();
    void otherwiseStatement();
    void variableDecl();
    void expression();

public:
    Parser(const char* filepath);
    AbstractSyntaxTree* parse();
    ~Parser();
};

