#pragma once

#include <iostream>

#include "Callable.h"
#include "StatementBlock.h"
#include "../RuntimeException.h"
#include "./Values/Object.h"
#include "Environment.h"
#include "Packets.h"
#include "ExceptionObjects.h"

class Function : public Value, public Callable {
    ptr<IdentifierList> parameters;
    ptr<StatementBlock> statementBlock;
    Object* owner;
public:
    Function(ptr<IdentifierList> parameters, ptr<StatementBlock> statementBlock)
        : owner(nullptr), parameters(parameters), statementBlock(statementBlock) { }

    ptr<Value> call(ValueList& arguments) override {
        if(!owner)
            throw ThrowPacket(ExceptionObjects::null_value("Function owner not set"));

        if(arguments.size() != parameters -> size())
            throw ThrowPacket(ExceptionObjects::call_failed("Invalid number of arguments"));

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
