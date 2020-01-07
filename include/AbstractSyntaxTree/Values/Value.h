#pragma once

#include "../Expression.h"
#include "../TypeDefinitions.h"
#include "../Type.h"

struct Value : public Expression {
    ptr<Value> getValue() override {
        return ptr<Value>(this);
    }

    virtual Type getType() = 0;
};
