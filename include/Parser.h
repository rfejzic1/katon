#pragma once

#include <string>
#include <vector>

#include "Klex.h"
#include "ParseException.h"
#include "AbstractSyntaxTree/TypeDefinitions.h"
#include "AbstractSyntaxTree/Scope.h"

class Expression;
class Object;
class Statement;
class StatementBlock;
class ValueSymbol;
class FunctionSymbol;
class Array;

class Parser {
    std::string filepath;
    Klex* klex;
    Token currentToken;

    int functionCounter = 0;

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

    ptr<Object> module();
    ptr<Object> object();
    ptr<Array> array();
    void memberDecl(ptr<Object>&);
    void attributeDecl(ptr<Object>& object, Scope scope);
    void method(ptr<Object> &object, Scope scope);
    IdentifierList identifierList();
    ExpressionList expressionList();
    void lambda();
    ptr<StatementBlock> statementBlock();
    std::vector<ptr<Statement>> statements();
    ptr<Statement> statement();
    ptr<Statement> ifStatement();
    ptr<Statement> whileStatement();
    ptr<Statement> forStatement();
    ptr<Statement> tryCatchStatement();
    ptr<Statement> otherwiseStatement(ptr<Statement> stat);
    ptr<Statement> continueStatement();
    ptr<Statement> breakStatement();
    ptr<Statement> returnStatement();
    ptr<Statement> throwStatement();
    ptr<Statement> localDecl(TokenType tokenType);
    ptr<Statement> expressionStatement();
    ptr<Expression> expression();
    void logOr();
    void logAnd();
    void equality();
    void comparison();
    void term();
    void factor();
    void unary();
    void primary();
    void merge();
    void value();
    void variable(Expression* callee);
    void postfix(Expression* callee);
    void call(Expression* callee);
    void access(Expression* callee);

public:
    explicit Parser(const char* filepath);
    ptr<Object> parse();
    ~Parser();
};
