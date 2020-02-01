#pragma once

#include <utility>

#include "UnaryOperator.h"
#include "../ExceptionObjects.h"
#include "../Packets.h"

class Cast : public UnaryOperator {
    Type type;
public:
    explicit Cast(ptr<Expression> expression, Type type) : UnaryOperator(std::move(expression)), type(type) {}

    ptr<Value> evaluate(Environment *env) override {
        ptr<Value> value = expression -> evaluate(env);

        if(type == Type::Object)
            return value -> asObject();
        else if(type == Type::Array)
            return value -> asArray();
        else if(type == Type::String)
            return make<String>(value -> asString());
        else if(type == Type::Double)
            return make<Double>(value -> asDouble());
        else if(type == Type::Integer)
            return make<Integer>(value -> asInteger());
        else if(type == Type::Boolean)
            return make<Boolean>(value -> asBoolean());

        throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value"));
    }
};
