#pragma once

#include "../Nodes.h"

struct Value : public Expression {
    virtual std::string asString() = 0;
    virtual long long int asInteger() = 0;
    virtual double asDouble() = 0;
    virtual bool asBoolean() = 0;

    Value* getValue() {
        return this;
    }
};
