#include "../include/AbstractSyntaxTree/Environment.h"

#include "../include/AbstractSyntaxTree/Symbol.h"
#include "../include/AbstractSyntaxTree/Values/Value.h"
#include "../include/AbstractSyntaxTree/Function.h"

bool Environment::hasSymbol(const Identifier& ident) {
    for(auto& it : symbols) {
        if(it.first.name == ident)
            return true;
    }
    return false;
}

void Environment::putValue(const Identifier &ident, Scope scope, ptr<Value> value, bool constant) {
    Symbol symbol(ident, constant, scope);
    symbols[symbol] = std::dynamic_pointer_cast<Member>(value);
}

void Environment::putFunction(const Identifier &ident, Scope scope, ptr<Function> function) {
    Symbol symbol(ident, true, scope);
    symbols[symbol] = std::dynamic_pointer_cast<Member>(function);
}

ptr<Member> Environment::getMember(const Identifier &ident) {
    return symbols[ident];
}

ptr<Member> Environment::getMemberDeep(const Identifier& ident) {
    Environment* currentEnv = this;
    while(currentEnv && !currentEnv -> hasSymbol(ident)) {
        currentEnv = currentEnv -> getEnclosing();
    }
    return currentEnv ? currentEnv -> getMember(ident) : nullptr;
}

ptr<Value> Environment::getValue(const Identifier &ident) {
    return std::dynamic_pointer_cast<Value>(getMemberDeep(ident));
}

ptr<Function> Environment::getFunction(const Identifier &ident) {
    return std::dynamic_pointer_cast<Function>(getMemberDeep(ident));
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
