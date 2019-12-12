#pragma once

#include "Node.h"

struct Symbol : public Node {
    const char* name;
    bool constant;

public:
    Symbol(const char* name, bool constant) : name(name), constant(constant) {}

    void accept(Interpreter interpreter) override {
        //
    }
};