#pragma once

#include "../TypeDefinitions.h"
#include "../Statement.h"
#include "../Expression.h"
#include "../Packets.h"

class ReturnStatement : public Statement {
    ptr<Expression> expression;
public:
    void execute(Environment *env) override {
        throw ReturnPacket(expression -> getValue());
    }
};
