#pragma once

#include "Value.h"
#include "../Environment.h"

class Object : public Value {
    Environment members;
public:
    Object() = default;
    Object(Environment* environment) : members(*environment) { }
    Environment* getEnvironment();

    Type getType() override;
    std::string asString() override;
    long long int asInteger() override;
    double asDouble() override;
    bool asBoolean() override;
    ptr<Object> asObject() override;
    ptr<Array> asArray() override;
};