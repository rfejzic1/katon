#pragma once

#include <utility>

#include "Operation.h"

class Multiplication : public Operation {
    ptr<Value> asIntegers(long long leftOperand, long long rightOperand) override {
        return make<Integer>(leftOperand * rightOperand);
    }

    ptr<Value> asDoubles(double leftOperand, double rightOperand) override {
        return make<Double>(leftOperand * rightOperand);
    }

    ptr<Value> asBooleans(bool leftOperand, bool rightOperand) override {
        return make<Boolean>(leftOperand * rightOperand);
    }
};
