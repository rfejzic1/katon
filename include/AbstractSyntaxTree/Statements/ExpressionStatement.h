#pragma once

#include "../TypeDefinitions.h"
#include "../Statement.h"
#include "../Expression.h"

class ExpressionStatement : public Statement {
    ptr<Expression> expression;
public:
    explicit ExpressionStatement(ptr<Expression> expression) : expression(std::move(expression)) { }
    void execute(Environment *env) override {
        expression -> getValue();
    }
};
