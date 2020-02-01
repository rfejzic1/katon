#pragma once

#include <utility>

#include "BinaryOperator.h"
#include "../Packets.h"
#include "../ExceptionObjects.h"

class Assignment : public BinaryOperator {
public:
    Assignment(ptr<Operation> operation, ptr<Symbol> left, ptr<Expression> right) : BinaryOperator(operation, left, right) { }

    ptr<Value> evaluate(Environment *env) override {
        ptr<Symbol> symbol = std::dynamic_pointer_cast<Symbol>(leftExpression);

        if(!symbol || !(env -> hasSymbol(symbol -> name)))
            throw ThrowPacket(ExceptionObjects::undefined("The member is not defined"));

        ptr<Value> currValue = env -> getValue(symbol -> name);
        ptr<Value> newValue = rightExpression -> evaluate(env);

        if(operation)
            newValue = operation -> getResult(currValue, newValue);

        env -> putValue(symbol -> name, symbol -> scope, newValue, symbol -> constant);
    }
};
