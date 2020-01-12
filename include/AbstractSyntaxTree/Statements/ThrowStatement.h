#pragma once

#include "../TypeDefinitions.h"
#include "../Statement.h"
#include "../Expression.h"
#include "../Packets.h"

class ThrowStatement : public Statement {
    ptr<Expression> expression;
public:
    explicit ThrowStatement(ptr<Expression> expression = nullptr) : expression(std::move(expression)) { }
    void execute(Environment *env) override {
        ptr<Value> toThrow = expression ? expression -> getValue() : nullptr;
        throw ThrowPacket(toThrow);
    }
};
