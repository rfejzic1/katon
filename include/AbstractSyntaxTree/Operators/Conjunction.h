#pragma once

#include <utility>

#include "BinaryOperator.h"

class Conjunction : public Operation {
    ptr<Value> asIntegers(long long leftOperand, long long rightOperand) override {
        return make<Boolean>(leftOperand && rightOperand);
    }

    ptr<Value> asDoubles(double leftOperand, double rightOperand) override {
        return make<Boolean>((bool) leftOperand && (bool) rightOperand);
    }

    ptr<Value> asBooleans(bool leftOperand, bool rightOperand) override {
        return make<Boolean>(leftOperand && rightOperand);
    }
};
