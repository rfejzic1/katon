#pragma once

#include "Environment.h"

class Object;

class ObjectBuilder {
    Environment members;
public:
    ObjectBuilder& putAttribute(const Identifier& ident, bool constant, ptr<Value> value, Scope scope = Scope::Public);
    ObjectBuilder& putFunction(const Identifier& ident, ptr<Function> function, Scope scope = Scope::Public);
    ObjectBuilder& merge(ptr<Object>& other);
    ptr<Value> build();
};
