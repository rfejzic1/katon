#pragma once

#include <utility>

#include "UnaryOperator.h"
#include "../ExceptionObjects.h"
#include "../Packets.h"

class Negation : public UnaryOperator {
public:
    explicit Negation(ptr<Expression> expression) : UnaryOperator(std::move(expression)) {}

    ptr<Value> evaluate(Environment *env) override {
        ptr<Value> value = expression -> evaluate(env);
        return make<Boolean>(!value -> asBoolean());;
    }
};
