#pragma once

#include <utility>

#include "BinaryOperator.h"

struct Addition : public BinaryOperator {
    Addition(ptr<Expression> left, ptr<Expression> right) : BinaryOperator(std::move(left), std::move(right)) {}
    ptr<Value> getValue() override {
        ptr<Value> leftVal = left -> getValue();
        ptr<Value> rightVal = right -> getValue();





    }
};
