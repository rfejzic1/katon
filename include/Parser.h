#pragma once

#include <string>
#include <vector>

#include "Klex.h"
#include "ParseException.h"
#include "AbstractSyntaxTree/TypeDefinitions.h"
#include "AbstractSyntaxTree/Scope.h"
#include "AbstractSyntaxTree/Environment.h"

class Expression;
class Object;
class Statement;
class StatementBlock;
class Array;
class ObjectDescriptor;

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

    ptr<ObjectDescriptor> module();
    ptr<ObjectDescriptor> object();
    ptr<Array> array();
    void memberDecl(ptr<ObjectDescriptor> &descriptor);
    void attributeDecl(ptr<ObjectDescriptor> &descriptor, Scope scope);
    void method(ptr<ObjectDescriptor> &descriptor, Scope scope);
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
    ptr<ObjectDescriptor> parse();
    ~Parser();
};
