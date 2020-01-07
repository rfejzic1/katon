#pragma once

#include "Callable.h"
#include "StatementBlock.h"

class Function : public Callable {
    int parameterCount;
    IdentifierList parameters;
    StatementBlock statementBlock;
public:
    Function(int parameterCount, const IdentifierList& parameters, const StatementBlock& statementBlock)
        : parameterCount(parameterCount), parameters(parameters), statementBlock(statementBlock) { }

    ptr<Value> call(const ValueList &arguments) override {
        // env novi
        // todo: Implement airing; return and throw statement within StatementBlock
        // make use of c++ exception handling and function stack to implement own???
        return nullptr;
    }
};
