#pragma once

#include <utility>

#include "BinaryOperator.h"
#include "../Packets.h"
#include "../ExceptionObjects.h"

class ElementAccess : public BinaryOperator {
public:
    ElementAccess(ptr<Expression> left, ptr<Expression> right) : BinaryOperator(nullptr, std::move(left), std::move(right)) { }

    ptr<Value> evaluate(Environment *env) override {
        ptr<Symbol> symbolLeft = std::dynamic_pointer_cast<Symbol>(leftExpression);

        if(!symbolLeft)
            throw ThrowPacket(ExceptionObjects::undefined("The identifier is not a symbol"));

        ptr<Value> member = env -> getValue(symbolLeft -> name);
        ptr<Array> array =  member -> asArray();
        long long int accessor = rightExpression -> evaluate(env) -> asInteger();
        return (*(array -> getValues()))[accessor];
    }
};
