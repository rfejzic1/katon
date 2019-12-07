#pragma once

#include <iostream>
#include "../Interpreter.h"

struct Node {
    virtual void accept(Interpreter interpreter) = 0;
    virtual void print(const char* content) {
        std::cout << content << std::endl;
    }
};