#pragma once

#include "../Expression.h"
#include "../TypeDefinitions.h"
#include "../Type.h"

struct Value : public Expression {
    ptr<Value> getValue() override {
        return ptr<Value>(this);
    }
    virtual std::string asString() = 0;
    virtual long long int asInteger() = 0;
    virtual double asDouble() = 0;
    virtual bool asBoolean() = 0;
    virtual Type getType() = 0;
};
