#pragma once

#include "AbstractSyntaxTree.h"

class MethodSymbol : public Symbol {
    ptr<Method> method;
public:
    MethodSymbol(const std::string &ident, ptr<Method> method)
            : Symbol(ident, true), method(method) {}
};
