#pragma once

#include "Callable.h"
#include "StatementBlock.h"

class Function : public Callable {
    IdentifierList parameters;
    StatementBlock statementBlock;
public:
    Function(const IdentifierList& parameters, const StatementBlock& statementBlock)
        : parameters(parameters), statementBlock(statementBlock) { }

    ptr<Value> call(const ValueList &arguments, Environment* callerEnv) override {
        // env novi
        // todo: Implement airing; return and throw statement within StatementBlock
        // make use of c++ exception handling and function stack to implement own???
        return nullptr;
    }
};
