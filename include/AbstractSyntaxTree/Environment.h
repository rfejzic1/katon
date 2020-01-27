#pragma once

#include <unordered_map>
#include <iostream>

#include "TypeDefinitions.h"
#include "Scope.h"
#include "Type.h"
#include "Symbol.h"

class Member;
class Value;
class Function;

class SymbolHashFunction {
public:
    std::size_t operator()(const Symbol& symbol) const {
        return std::hash<std::string>()(symbol.name);
    }
};

class Environment {
    Environment* enclosing;
    std::unordered_map<Symbol, ptr<Member>, SymbolHashFunction> symbols;

    ptr<Member> getMemberDeep(const Identifier& ident);

public:
    explicit Environment(Environment* enclosing = nullptr) : enclosing(enclosing) { }
    void putValue(const Identifier &ident, Scope scope, ptr<Value> value, bool constant);
    void putFunction(const Identifier& ident, Scope scope, ptr<Function> function);
    bool hasSymbol(const Identifier& ident);
    ptr<Member> getMember(const Identifier& ident);
    ptr<Value> getValue(const Identifier& ident);
    ptr<Function> getFunction(const Identifier& ident);
    void merge(Environment* other);

    Environment* getEnclosing();
    void setEnclosing(Environment* enclosing);

    ~Environment() { };
};
