#pragma once

#include "../Expression.h"

class ArrayExpression: public Expression {
public:
    ptr<Value> evaluate(Environment *env) override;
};
