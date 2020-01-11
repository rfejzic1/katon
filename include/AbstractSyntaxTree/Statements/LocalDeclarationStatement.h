#pragma once

#include "../TypeDefinitions.h"
#include "../StatementBlock.h"
#include "../Environment.h"
#include "../Function.h"

class LocalDeclarationStatement : public Statement {
    Identifier identifier;
    bool constant;
    ptr<Expression> expression;
public:
    LocalDeclarationStatement(Identifier& identifier, bool constant, ptr<Expression>& expression)
        : identifier(identifier), constant(constant), expression(expression) { }

    void execute(Environment *env) override {
        ptr<Value> value = expression -> getValue();
        env -> putAttribute(identifier, constant, value);
    }
};