#pragma once

#include "../Expression.h"

class ArrayExpression: public Expression {
    ptr<ExpressionList> elements;
public:
    ArrayExpression();
    explicit ArrayExpression(const ExpressionList& expressionList);
    ptr<Value> evaluate(Environment *env) override;
};
