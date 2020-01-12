#pragma once

#include <unordered_map>

#include "TypeDefinitions.h"
#include "Scope.h"

class ValueSymbol;
class FunctionSymbol;
class Value;
class Symbol;
class Function;

class Environment {
    std::unordered_map<std::string, ptr<Symbol>> symbols;
    Environment* enclosing;
public:
    explicit Environment(Environment* enclosing = nullptr) : enclosing(enclosing) { }
    bool hasMember(const Identifier& ident);
    bool putAttribute(const Identifier& ident, bool constant, ptr<Value> value, Scope scope = Scope::Public);
    bool putFunction(const Identifier& ident, ptr<Function> function, Scope scope = Scope::Public);
    ptr<Symbol> getMember(const Identifier& ident);
    ptr<Symbol> getMemberIncludingFromEnclosingEnvironments(const Identifier& ident);
    ptr<ValueSymbol> getAttribute(const Identifier& ident);
    ptr<ValueSymbol> getAttributeIncludingFromEnclosingEnvironments(const Identifier& ident);
    ptr<FunctionSymbol> getFunction(const Identifier& ident);
    ptr<FunctionSymbol> getFunctionIncludingFromEnclosingEnvironments(const Identifier& ident);
    Environment* getEnclosing();
    void setEnclosing(Environment* enclosing);
};
