#pragma once

#include "../Expression.h"
#include "Operation.h"

class UnaryOperator : public Expression {
protected:
    ptr<Expression> expression;
public:
    explicit UnaryOperator(ptr<Expression> expression) : expression(std::move(expression)) {}
};
