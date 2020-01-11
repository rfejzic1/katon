#pragma once

#include "Type.h"
#include "Expression.h"

struct Symbol : public Expression {
    std::string name;
    bool constant;
    Type type;
public:
    Symbol(Identifier name, bool constant, Type type) : name(std::move(name)), constant(constant), type(type) {}
};
