#pragma once

#include <utility>

#include "BinaryOperator.h"
#include "../Packets.h"
#include "../ExceptionObjects.h"

class MemberAccess : public BinaryOperator {
public:
    MemberAccess(ptr<Expression> left, ptr<Expression> right) : BinaryOperator(nullptr, std::move(left), std::move(right)) { }

    ptr<Value> evaluate(Environment *env) override {
        ptr<Symbol> symbolLeft = std::dynamic_pointer_cast<Symbol>(leftExpression);
        ptr<Symbol> symbolRight = std::dynamic_pointer_cast<Symbol>(rightExpression);

        if(!symbolLeft || !symbolRight)
            throw ThrowPacket(ExceptionObjects::undefined("The identifier is not a symbol"));

        ptr<Value> currValue = env -> getValue(symbolLeft -> name);
        ptr<Object> object = currValue -> asObject();
        ptr<Value> value = object -> getAttribute(symbolRight -> name);

        if(!value)
            throw ThrowPacket(ExceptionObjects::undefined("Member not defined"));

        return value;
    }
};
