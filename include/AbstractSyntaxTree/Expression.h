#pragma once

#include "Values/Value.h"
#include "Statement.h"

class Value;

struct Expression : public Statement {
    virtual ptr<Value> getValue() = 0;
};
