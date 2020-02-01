#pragma once

#include <utility>

#include "UnaryOperator.h"
#include "../Packets.h"
#include "../ExceptionObjects.h"
#include "../Callable.h"

class Call : public UnaryOperator {
    ExpressionList expressionList;
public:
    Call(ptr<Expression> callee, ExpressionList& expressionList) : UnaryOperator(callee), expressionList(expressionList) { }

    ptr<Value> evaluate(Environment *env) override {
        ptr<Value> value = expression -> evaluate(env);
        ptr<Callable> callable = std::dynamic_pointer_cast<Callable>(value);

        if(!callable)
            throw ThrowPacket(ExceptionObjects::call_failed("Value not callable"));

        ValueList values;
        for(auto& expr : expressionList)
            values.push_back(expr -> evaluate(env));

        return callable->call(values);
    }
};
