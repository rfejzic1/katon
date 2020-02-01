#pragma once

#include "TypeDefinitions.h"
class Object;

struct Callable {
    virtual Object* getCaller() = 0;
    virtual ptr<Value> call(ValueList &arguments) = 0;
};
