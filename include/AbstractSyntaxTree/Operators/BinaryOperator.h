#pragma once

#include "../Expression.h"

struct BinaryOperator : public Expression {
    ptr<Expression> left = nullptr;
    ptr<Expression> right = nullptr;

    BinaryOperator() = default;
    BinaryOperator(Expression* left, Expression* right) : left(left), right(right) {}

};
