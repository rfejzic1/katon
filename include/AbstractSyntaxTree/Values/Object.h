#pragma once

#include "Value.h"
#include "../Method.h"
#include "../ValueSymbol.h"
#include "../MethodSymbol.h"

class Object : public Value {
    SymbolMap members;
public:
    bool hasMember(const std::string& ident);
    bool putAttribute(const std::string& ident, bool constant, ptr<Value>& value);
    bool putMethod(const std::string& ident, ptr<Method>& method);
    ptr<Symbol> getMember(const std::string& ident);
};