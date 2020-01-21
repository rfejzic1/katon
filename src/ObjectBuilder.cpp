#include "../include/AbstractSyntaxTree/ObjectBuilder.h"

#include "../include/AbstractSyntaxTree/Values/Object.h"

ObjectBuilder &ObjectBuilder::putAttribute(const Identifier &ident, bool constant, ptr<Value> value, Scope scope) {
    members.putAttribute(ident, constant, std::move(value), scope);
    return *this;
}

ObjectBuilder &ObjectBuilder::putFunction(const Identifier &ident, ptr<Function> function, Scope scope) {
    members.putFunction(ident, std::move(function), scope);
    return *this;
}

ObjectBuilder &ObjectBuilder::merge(ptr<Object> &other) {
    members.merge(other -> getEnvironment());
    return *this;
}

ptr<Value> ObjectBuilder::build() {
    return std::make_shared<Object>(&members);
}
