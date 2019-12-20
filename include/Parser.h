#pragma once

#include <string>
#include <vector>

#include "AbstractSyntaxTree/AbstractSyntaxTree.h"
#include "Klex.h"

class Parser {
    std::string filepath;
    Klex* klex;
    AbstractSyntaxTree* astree;
    Token currentToken;

    void openKlex();
    void checkKlex();
    void closeKlex();

    Token token();
    void printToken();
    void consume(TokenType tokenType, const char* what);
    void consume();
    bool match(TokenType type);
    bool matchAny(const std::vector<TokenType>& types);
    void unexpected();
    void expected(const char* what);
    static void error(const char* message);
    static void log(const char* message);

    void object();
    void memberDecl();
    void attributeDecl();
    void method();
    void identifierList();
    void statementBlock();
    void statements();
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

