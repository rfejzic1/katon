#pragma once

#include "Value.h"
#include "../Environment.h"

class Object : public Value {
    Environment members;
public:
    Object() = default;
    Object(Environment members) : members(std::move(members)) {}

    ptr<Member> getMember(const Identifier& ident);
    ptr<Value> getAttribute(const Identifier& ident);
    ptr<Function> getFunction(const Identifier& ident);

    Environment* getEnvironment();

    Type getType() override;
    std::string asString() override;
    long long int asInteger() override;
    double asDouble() override;
    bool asBoolean() override;
    ptr<Object> asObject() override;
    ptr<Array> asArray() override;

    virtual ~Object() { }
};
