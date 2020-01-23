#pragma once

#include "TypeDefinitions.h"
class Object;

struct Callable {
    virtual ptr<Value> call(ptr<Object> caller, ValueList &arguments) = 0;
};
