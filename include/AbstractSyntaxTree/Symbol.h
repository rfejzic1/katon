#pragma once

#include "unordered_map"
#include <string>

#include "Type.h"
#include "Expression.h"
#include "Scope.h"

struct Symbol : public Expression {
    std::string name;
    bool constant;
    Scope scope;
public:
    Symbol(Identifier name, bool constant, Scope scope = Scope::Public)
        : name(name), constant(constant), scope(scope) {}

    Symbol(Identifier name) : name(name), constant(false), scope(Scope::Public) {}

    ptr<Value> evaluate(Environment* env) override;
    bool operator == (const Symbol& symbol) const;

    virtual ~Symbol() {}
};
