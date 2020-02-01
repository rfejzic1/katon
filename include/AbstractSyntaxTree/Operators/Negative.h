#pragma once

#include <utility>

#include "UnaryOperator.h"
#include "../Packets.h"
#include "../ExceptionObjects.h"

class Negative : public UnaryOperator {
public:
    explicit Negative(ptr<Expression> expression) : UnaryOperator(std::move(expression)) {}

    ptr<Value> evaluate(Environment *env) override {
        ptr<Value> value = expression -> evaluate(env);
        Type type = value -> getType();

        if(type == Type::Double) {
            return make<Double>(-value -> asDouble());
        }
        if(type == Type::Integer) {
            return make<Integer>(-value -> asInteger());
        }
        if(type == Type::Boolean) {
            return make<Boolean>(-value -> asBoolean());
        }

        throw ThrowPacket(ExceptionObjects::undefined_operation("Undefined operation for this type"));
    }
};
