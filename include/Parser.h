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

    void module();
    void object();
    void array();
    void memberDecl();
    void attributeDecl();
    void method();
    void identifierList();
    void expressionList();
    void lambda();
    void statementBlock();
    void statements();
    void statement();
    void ifStatement();
    void whileStatement();
    void forStatement();
    void tryCatchStatement();
    void otherwiseStatement();
    void continueStatement();
    void breakStatement();
    void returnStatement();
    void throwStatement();
    void localDecl();
    void expression();
    void logOr();
    void logAnd();
    void equality();
    void comparison();
    void term();
    void factor();
    void unary();
    void primary();
    void value();
    void variable(Expression* callee);
    void postfix(Expression* callee);
    void call(Expression* callee);
    void access(Expression* callee);

public:
    Parser(const char* filepath);
    AbstractSyntaxTree* parse();
    ~Parser();
};

