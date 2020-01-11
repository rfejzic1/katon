#pragma once

#include "TypeDefinitions.h"
class Object;

struct Callable {
    virtual ptr<Value> call(Object* caller, ValueList &arguments) = 0;
};
