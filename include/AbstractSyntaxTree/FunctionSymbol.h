#pragma once

#include "TypeDefinitions.h"
#include "Symbol.h"

class FunctionSymbol : public Symbol {
    ptr<Function> function;
public:
    FunctionSymbol(const std::string &ident, ptr<Function> function)
            : Symbol(ident, true, Type::Function), function(function) {}

    ptr<Function> getFunction() {
        return function;
    }
};
