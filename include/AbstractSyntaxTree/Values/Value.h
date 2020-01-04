#pragma once

#include "../Expression.h"

struct Value : public Expression {
    ptr<Value> getValue() override {
        return ptr<Value>(this);
    }
};
