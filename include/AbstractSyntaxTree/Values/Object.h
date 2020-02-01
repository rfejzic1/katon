#pragma once

#include "Value.h"
#include "../Environment.h"
#include "../Callable.h"

class Object : public Value, public Callable {
    Environment members;
public:
    Object() = default;
    Object(Environment members) : members(std::move(members)) {}

    ptr<Member> getMember(const Identifier& ident);
    ptr<Value> getAttribute(const Identifier& ident);
    ptr<Function> getFunction(const Identifier& ident);

    Environment* getEnvironment();
    void setEnvironment(Environment* env);
    void merge(ptr<Object> other);

    Type getType() override;
    std::string asString() override;
    long long int asInteger() override;
    double asDouble() override;
    bool asBoolean() override;
    ptr<Object> asObject() override;
    ptr<Array> asArray() override;

    ptr<Value> call(ValueList &arguments) override;
    Object* getCaller() override;

    virtual ~Object() { }
};
