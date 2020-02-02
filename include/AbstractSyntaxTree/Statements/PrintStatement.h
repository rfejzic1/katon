#pragma once

#include "../TypeDefinitions.h"
#include "../Statement.h"

#include <utility>
#include <iostream>
#include "../Expression.h"
#include "../Packets.h"
#include "../ExceptionObjects.h"

class PrintStatement : public Statement {
    ptr<Expression> expression;
public:
    explicit PrintStatement(ptr<Expression> expression) : expression(std::move(expression)) { }
    void execute(Environment *env) override {
        if(!expression)
            throw ThrowPacket(ExceptionObjects::null_value("Value is null"));
        ptr<Value> value = expression -> evaluate(env);
        if(!value)
            throw ThrowPacket(ExceptionObjects::null_value("Value is null"));

        std::cout << value -> asString();
    }
};
