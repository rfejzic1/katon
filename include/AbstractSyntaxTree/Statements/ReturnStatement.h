#pragma once

#include "../TypeDefinitions.h"
#include "../Statement.h"
#include "../Expression.h"
#include "../Packets.h"

class ReturnStatement : public Statement {
    ptr<Expression> expression;
public:
    explicit ReturnStatement(ptr<Expression> expression = nullptr) : expression(std::move(expression)) { }
    void execute(Environment *env) override {
        ptr<Value> toReturn = expression ? expression -> getValue() : nullptr;
        throw ReturnPacket(toReturn);
    }
};
