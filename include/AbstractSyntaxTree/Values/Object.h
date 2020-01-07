#pragma once

#include "Value.h"

class Function;
class Symbol;

class Object : public Value {
    SymbolMap members;
public:
    bool hasMember(const std::string& ident);
    bool putAttribute(const std::string& ident, bool constant, ptr<Value>& value);
    bool putMethod(const std::string& ident, ptr<Function>& method);
    ptr<Symbol> getMember(const std::string& ident);
    Type getType() override;
};