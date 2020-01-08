#include "../include/AbstractSyntaxTree/Environment.h"

#include "../include/AbstractSyntaxTree/ValueSymbol.h"
#include "../include/AbstractSyntaxTree/FunctionSymbol.h"

bool Environment::hasMember(const std::string &ident) {
    return symbols.find(ident) != symbols.end();
}

bool Environment::putAttribute(const std::string &ident, bool constant, ptr<Value>& value) {
    bool hadMember = hasMember(ident);
    symbols[ident] = std::make_shared<ValueSymbol>(ident, constant, value);
    return hadMember;
}

bool Environment::putFunction(const std::string &ident, ptr<Function>& method) {
    bool hadMember = hasMember(ident);
    symbols[ident] = std::make_shared<FunctionSymbol>(ident, method, this);
    return hadMember;
}

ptr<Symbol> Environment::getMember(const std::string &ident) {
    return symbols[ident];
}

