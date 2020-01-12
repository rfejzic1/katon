#pragma once

#include "TypeDefinitions.h"
#include "Symbol.h"
#include "Function.h"

class Object;

class FunctionSymbol : public Symbol {
    ptr<Function> function;
public:
    FunctionSymbol(Identifier ident, ptr<Function> function, Scope scope = Scope::Public)
            : Symbol(std::move(ident), false, Type::Function, scope), function(std::move(function)) {}

    ptr<Function> getFunction() {
        return function;
    }

    virtual ptr<Value> getValue() override {
        return nullptr;
    }
};
