#pragma once

#include "BinaryOperator.h"

struct Addition : public BinaryOperator {
    Addition(ptr<Expression> left, ptr<Expression> right) : BinaryOperator(left, right) {}
    ptr<Value> getValue() override {
        ptr<Value> leftVal = left -> getValue();
        ptr<Value> rightVal = right -> getValue();





    }
};
