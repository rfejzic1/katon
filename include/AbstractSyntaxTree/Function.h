#pragma once

#include <iostream>

#include "Callable.h"
#include "StatementBlock.h"
#include "../RuntimeException.h"
#include "./Values/Object.h"
#include "Environment.h"

class Function : public Callable {
    IdentifierList parameters;
    StatementBlock statementBlock;
public:
    Function(IdentifierList parameters, StatementBlock statementBlock)
        : parameters(std::move(parameters)), statementBlock(std::move(statementBlock)) { }

    ptr<Value> call(ptr<Object> caller, ValueList& arguments) override {
        if(arguments.size() != parameters.size())
            throw RuntimeException("Number of arguments does not match number of parameters!");

        Environment localEnv = *(caller -> getEnvironment());

        for(int i = 0; i < arguments.size(); i++)
            localEnv.putAttribute(parameters[i], false, arguments[i]);

        try {
            statementBlock.execute(&localEnv);
        } catch(ptr<Value> value) {
            return value;
        }

        return nullptr;
    }
};
