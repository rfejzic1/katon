#pragma once

#include "../Expression.h"
#include "Operation.h"

class BinaryOperator : public Expression {
protected:
    ptr<Expression> leftExpression;
    ptr<Expression> rightExpression;
    ptr<Operation> operation;
public:
    BinaryOperator(ptr<Operation> operation, ptr<Expression> left, ptr<Expression> right);
    ptr<Value> evaluate(Environment* env) override;
};
