#include "../include/AbstractSyntaxTree/ObjectBuilder.h"

#include "../include/AbstractSyntaxTree/Values/Object.h"

ObjectBuilder &ObjectBuilder::putAttribute(const Identifier &ident, bool constant, ptr<Value> value, Scope scope) {
    members.putValue(ident, scope, std::move(value), constant);
    return *this;
}

ObjectBuilder &ObjectBuilder::putFunction(const Identifier &ident, ptr<Function> function, Scope scope) {
    members.putFunction(ident, scope, std::move(function));
    return *this;
}

ObjectBuilder &ObjectBuilder::merge(ptr<Object> &other) {
    members.merge(other -> getEnvironment());
    return *this;
}

ptr<Value> ObjectBuilder::build() {
    return make<Object>(&members);
}
