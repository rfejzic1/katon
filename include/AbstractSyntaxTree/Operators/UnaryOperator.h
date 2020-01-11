#pragma once

#include "../Expression.h"

struct UnaryOperator : public Expression {
    ptr<Expression> operand = nullptr;
    explicit UnaryOperator(ptr<Expression>& operand) : operand(operand) {}
};
