#pragma once

#include <utility>

#include "BinaryOperator.h"

class LessThan : public Operation {
    ptr<Value> asStrings(const std::string &leftOperand, const std::string &rightOperand) override {
        return make<Boolean>(leftOperand < rightOperand);
    }

    ptr<Value> asIntegers(long long leftOperand, long long rightOperand) override {
        return make<Boolean>(leftOperand < rightOperand);
    }

    ptr<Value> asDoubles(double leftOperand, double rightOperand) override {
        return make<Boolean>((bool) leftOperand < (bool) rightOperand);
    }

    ptr<Value> asBooleans(bool leftOperand, bool rightOperand) override {
        return make<Boolean>(leftOperand < rightOperand);
    }
};
