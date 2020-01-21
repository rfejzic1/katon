#include "../include/AbstractSyntaxTree/Environment.h"

#include "../include/AbstractSyntaxTree/ValueSymbol.h"
#include "../include/AbstractSyntaxTree/FunctionSymbol.h"

bool Environment::hasMember(const Identifier& ident) {
    return symbols.find(ident) != symbols.end();
}

bool Environment::putAttribute(const Identifier &ident, bool constant, ptr<Value> value, Scope scope) {
    bool hadMember = hasMember(ident);
    symbols[ident] = make<ValueSymbol>(ident, constant, std::move(value), scope);
    return hadMember;
}

bool Environment::putFunction(const Identifier &ident, ptr<Function> function, Scope scope) {
    bool hadMember = hasMember(ident);
    symbols[ident] = make<FunctionSymbol>(ident, std::move(function), scope);
    return hadMember;
}

ptr<Symbol> Environment::getMember(const Identifier &ident) {
    return symbols[ident];
}

ptr<Symbol> Environment::getMemberIncludingFromEnclosingEnvironments(const Identifier& ident) {
    Environment* currentEnv = this;
    while(currentEnv && !currentEnv -> hasMember(ident)) {
        currentEnv = currentEnv -> getEnclosing();
    }
    return currentEnv ? currentEnv -> getMember(ident) : nullptr;
}

ptr<ValueSymbol> Environment::getAttribute(const Identifier& ident) {
    return std::dynamic_pointer_cast<ValueSymbol>(getMember(ident));
}
ptr<ValueSymbol> Environment::getAttributeIncludingFromEnclosingEnvironments(const Identifier& ident) {
    return std::dynamic_pointer_cast<ValueSymbol>(getMemberIncludingFromEnclosingEnvironments(ident));
}
ptr<FunctionSymbol> Environment::getFunction(const Identifier& ident) {
    return std::dynamic_pointer_cast<FunctionSymbol>(getMember(ident));
}
ptr<FunctionSymbol> Environment::getFunctionIncludingFromEnclosingEnvironments(const Identifier& ident) {
    return std::dynamic_pointer_cast<FunctionSymbol>(getMemberIncludingFromEnclosingEnvironments(ident));
}

Environment *Environment::getEnclosing() {
    return enclosing;
}

void Environment::setEnclosing(Environment *newEnclosing) {
    enclosing = newEnclosing;
}

void Environment::merge(Environment *other) {
    for(auto& it : other -> symbols) {
        symbols[it.first] = it.second;
    }
}
