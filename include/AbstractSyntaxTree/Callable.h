#pragma once

#include "TypeDefinitions.h"
class Environment;

struct Callable {
    virtual ptr<Value> call(const ValueList &arguments, Environment* callerEnv) = 0;
};
