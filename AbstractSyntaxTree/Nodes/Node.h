#pragma once

#include "../../Interpreter/Interpreter.h"

struct Node {
    virtual void accept(Interpreter interpreter) = 0;
};