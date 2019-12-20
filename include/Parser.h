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
    void consume(TokenType tokenType, const char* message);
    void consume();
    bool match(TokenType type);
    bool matchAny(const std::vector<TokenType>& types);
    static void error(const char* message);
    static void log(const char* message);

    void object();
    void attributeDecl();
    void method();
    void identifierList();
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

