#include "../include/AbstractSyntaxTree/Values/Object.h"

#include <memory>

bool Object::hasMember(const std::string &ident) {
    return members.find(ident) != members.end();
}

bool Object::putAttribute(const std::string &ident, bool constant, ptr<Value>& value) {
    bool hadMember = hasMember(ident);
    members[ident] = std::make_shared<ValueSymbol>(ident, constant, value);
    return hadMember;
}

bool Object::putMethod(const std::string &ident, ptr<Method>& method) {
    bool hadMember = hasMember(ident);
    members[ident] = std::make_shared<MethodSymbol>(ident, method);
    return hadMember;
}

ptr<Symbol> Object::getMember(const std::string &ident) {
    return members[ident];
}
