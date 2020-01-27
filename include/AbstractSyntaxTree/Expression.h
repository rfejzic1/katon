#pragma once

#include "TypeDefinitions.h"

class Environment;

struct Expression {
    virtual ptr<Value> evaluate(Environment* env) = 0;
    virtual ~Expression() {}
};
