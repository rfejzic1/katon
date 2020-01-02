#pragma once

#include "../Nodes.h"
#include "../Expression.h"

struct Value : public Expression {


    ptr<Value> getValue() {
        return ptr<Value>(this);
    }

    void accept(Interpreter interpreter) override {}
};
