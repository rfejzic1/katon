#pragma once

#include "TypeDefinitions.h"
#include "Symbol.h"
#include "Function.h"

class Object;

class FunctionSymbol : public Symbol {
    ptr<Function> function;
    Environment* ownerEnv;
public:
    FunctionSymbol(const std::string &ident, ptr<Function> function, Environment* ownerEnv)
            : Symbol(ident, false, Type::Function), function(function), ownerEnv(ownerEnv) {}

    ptr<Function> getFunction() {
        return function;
    }
};
