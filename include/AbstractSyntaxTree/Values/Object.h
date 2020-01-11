#pragma once

#include "Value.h"
#include "../Environment.h"

class Object : public Value {
    Environment members;
public:
    Environment* getEnvironment();
    Type getType() override;
    std::string asString() override;
    long long int asInteger() override;
    double asDouble() override;
    bool asBoolean() override;
};