#pragma once

#include <utility>
#include <cmath>

#include "Operation.h"

class Exponentiation : public Operation {
    ptr<Value> asIntegers(long long leftOperand, long long rightOperand) override {
        return make<Integer>(std::pow(leftOperand, rightOperand));
    }

    ptr<Value> asDoubles(double leftOperand, double rightOperand) override {
        return make<Double>(std::pow(leftOperand, rightOperand));
    }

    ptr<Value> asBooleans(bool leftOperand, bool rightOperand) override {
        return make<Boolean>(std::pow(leftOperand, rightOperand));
    }
};
