#pragma once

#include "Type.h"

struct Symbol : public Expression {
    const std::string& name;
    bool constant;
    Type type;
public:
    Symbol(const std::string& name, bool constant, Type type) : name(name), constant(constant), type(type) {}
};
