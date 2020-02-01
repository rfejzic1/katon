#pragma once

#include <iostream>

#include "Callable.h"
#include "StatementBlock.h"
#include "../RuntimeException.h"
#include "./Values/Object.h"
#include "Environment.h"

class Function : public Value, public Callable {
    ptr<IdentifierList> parameters;
    ptr<StatementBlock> statementBlock;
    Object* owner;
public:
    Function(ptr<IdentifierList> parameters, ptr<StatementBlock> statementBlock)
        : owner(nullptr), parameters(parameters), statementBlock(statementBlock) { }

    ptr<Value> call(ValueList& arguments) override {
        if(!owner)
            throw RuntimeException("Function owner not set!!!!");

        if(arguments.size() != parameters -> size())
            throw RuntimeException("Number of arguments does not match number of parameters!");

        Environment localEnv = *(owner -> getEnvironment());

        for(int i = 0; i < arguments.size(); i++)
            localEnv.putValue((*parameters)[i], Scope::Public, arguments[i], false);

        try {
            statementBlock -> execute(&localEnv);
        } catch(ptr<Value> value) {
            return value;
        }

        return nullptr;
    }

    void setOwner(Object* newOwner) {
        owner = newOwner;
    }

    Object * getCaller() override {
        return owner;
    }

    Type getType() override {
        return Type::Function;
    }
};
