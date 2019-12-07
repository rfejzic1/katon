#pragma once

#include "../Interpreter.h"

struct Node {
    virtual void accept(Interpreter interpreter) = 0;
};