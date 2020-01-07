#pragma once

#include "TypeDefinitions.h"

struct Callable {
    virtual ptr<Value> call(const ValueList &arguments) = 0;
};
