#pragma once

#include "../Interpreter.h"

struct Executable {
    virtual void execute(Interpreter interpreter) = 0;
};
