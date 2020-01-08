#pragma once

#include <unordered_map>

#include "Values/Value.h"
#include "Symbol.h"
#include "Function.h"

class Environment {
    std::unordered_map<std::string, ptr<Symbol>> symbols;
public:
    bool hasMember(const std::string& ident);
    bool putAttribute(const std::string& ident, bool constant, ptr<Value>& value);
    bool putFunction(const std::string& ident, ptr<Function>& method);
    ptr<Symbol> getMember(const std::string& ident);
};