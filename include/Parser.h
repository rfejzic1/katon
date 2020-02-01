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
class ArrayExpression;
class ObjectExpression;

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
    void error(const char* message);
    static void log(const char* message);

    ptr<ObjectExpression> module();
    ptr<ObjectExpression> object();
    ptr<ArrayExpression> array();
    void memberDecl(ptr<ObjectExpression> &descriptor);
    void attributeDecl(ptr<ObjectExpression> &descriptor, Scope scope);
    void method(ptr<ObjectExpression> &descriptor, Scope scope);
    IdentifierList identifierList();
    ExpressionList expressionList();
    ptr<Expression> lambda();
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
    ptr<Expression> disjunction();
    ptr<Expression> conjunction();
    ptr<Expression> equality();
    ptr<Expression> comparison();
    ptr<Expression> term();
    ptr<Expression> factor();
    ptr<Expression> merge();
    ptr<Expression> unary();
    ptr<Expression> castable();
    ptr<Expression> primary();
    ptr<Expression> value();
    void variable(Expression* callee);
    void postfix(Expression* callee);
    void call(Expression* callee);
    void access(Expression* callee);

public:
    explicit Parser(const char* filepath);
    ptr<ObjectExpression> parse();
    ~Parser();
};
