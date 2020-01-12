#pragma once

#include "Type.h"
#include "Expression.h"
#include "Scope.h"

struct Symbol : public Expression {
    std::string name;
    bool constant;
    Scope scope;
    Type type;
public:
    Symbol(Identifier name, bool constant, Type type, Scope scope = Scope::Public)
        : name(std::move(name)), constant(constant), type(type), scope(scope) {}
};
