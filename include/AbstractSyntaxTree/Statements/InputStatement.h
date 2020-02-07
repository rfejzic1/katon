#pragma once

#include "../TypeDefinitions.h"
#include "../Statement.h"

#include <utility>
#include <iostream>
#include "../Expression.h"
#include "../Packets.h"
#include "../ExceptionObjects.h"
#include "../Symbol.h"
#include "../Environment.h"
#include "../Values/String.h"

class InputStatement : public Statement {
    ptr<Expression> expression;
public:
    explicit InputStatement(ptr<Expression> symbol) : expression(std::move(symbol)) { }
    void execute(Environment *env) override {
        if(!expression)
            return;

        ptr<Symbol> symbol = std::dynamic_pointer_cast<Symbol>(expression);

        if(!symbol)
            throw ThrowPacket(ExceptionObjects::undefined_operation("Symbol not provided!"));

        if(!env->hasSymbol(symbol -> name))
            throw ThrowPacket(ExceptionObjects::undefined("Symbol not defined!"));

        std::string input;
        std::getline(std::cin, input);

        env->putValue(symbol->name, symbol->scope, make<String>(input), symbol->constant);
    }
};
