#pragma once

#include "../Nodes.h"
#include "../Expression.h"

struct Value : public Expression {
    virtual std::string asString() = 0;
    virtual long long int asInteger() = 0;
    virtual double asDouble() = 0;
    virtual bool asBoolean() = 0;

    ptr<Value> getValue() {
        return ptr<Value>(this);
    }

    void accept(Interpreter interpreter) override {}
};
