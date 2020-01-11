#pragma once

#include <unordered_map>

#include "TypeDefinitions.h"

class Value;
class Symbol;
class Function;

class Environment {
    std::unordered_map<std::string, ptr<Symbol>> symbols;
    Environment* enclosing;
public:
    explicit Environment(Environment* enclosing = nullptr) : enclosing(enclosing) { }
    bool hasMember(const std::string& ident);
    bool putAttribute(const std::string& ident, bool constant, ptr<Value>& value);
    bool putFunction(const std::string& ident, ptr<Function>& function);
    ptr<Symbol> getMember(const std::string& ident);
    ptr<Symbol> getMemberIncludingFromEnclosingEnvironments(const std::string& ident);
    Environment* getEnclosing();
    void setEnclosing(Environment* enclosing);
};
