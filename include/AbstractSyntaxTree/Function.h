#pragma once

#include <iostream>

#include "Callable.h"
#include "StatementBlock.h"
#include "../RuntimeException.h"
#include "./Values/Object.h"
#include "Environment.h"

class Function : public Member, public Callable {
    IdentifierList parameters;
    StatementBlock statementBlock;
public:
    Function(IdentifierList parameters, StatementBlock statementBlock)
        : parameters(parameters), statementBlock(statementBlock) { }

    ptr<Value> call(ptr<Object> caller, ValueList& arguments) override {
        if(arguments.size() != parameters.size())
            throw RuntimeException("Number of arguments does not match number of parameters!");

        Environment localEnv = *(caller -> getEnvironment());

        for(int i = 0; i < arguments.size(); i++)
            localEnv.putValue(parameters[i], Scope::Public, arguments[i], false);

        try {
            statementBlock.execute(&localEnv);
        } catch(ptr<Value> value) {
            return value;
        }

        return nullptr;
    }
};
