#pragma once

#include "TypeDefinitions.h"
#include "Statement.h"

struct Expression : public Statement {
    virtual ptr<Value> getValue() = 0;
    void execute(Environment *env) override { }
};
