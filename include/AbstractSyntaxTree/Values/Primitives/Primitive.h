#pragma once

#include "../Value.h"

struct Primitive : public Value {
    virtual std::string asString() = 0;
    virtual long long int asInteger() = 0;
    virtual double asDouble() = 0;
    virtual bool asBoolean() = 0;

};