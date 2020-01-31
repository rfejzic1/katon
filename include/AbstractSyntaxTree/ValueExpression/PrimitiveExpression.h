#pragma once

#include "../Expression.h"

template<class T>
class PrimitiveExpression: public Expression {
    T value;
public:
    PrimitiveExpression() = default;
    explicit PrimitiveExpression(T value) : value(value) {}
    ptr<Value> evaluate(Environment *env) override {
        return make<T>(value);
    }
};
