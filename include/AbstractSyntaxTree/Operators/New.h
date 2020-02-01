#pragma once

#include <utility>

#include "UnaryOperator.h"

class New : public UnaryOperator {
public:
    explicit New(ptr<Expression> expression) : UnaryOperator(std::move(expression)) {}

    ptr<Value> evaluate(Environment *env) override {
        ptr<Value> value = expression -> evaluate(env);
        return value -> asObject();
    }
};
