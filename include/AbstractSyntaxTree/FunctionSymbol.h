#pragma once

#include "TypeDefinitions.h"
#include "Symbol.h"
#include "Function.h"

class Object;

class FunctionSymbol : public Symbol {
    ptr<Function> function;
public:
    FunctionSymbol(const std::string &ident, ptr<Function> function)
            : Symbol(ident, false, Type::Function), function(function) {}

    ptr<Function> getFunction() {
        return function;
    }

    virtual ptr<Value> getValue() override {
        return nullptr;
    }
};
