#pragma once

#include "TypeDefinitions.h"

struct Expression {
    virtual ptr<Value> getValue() = 0;
};
