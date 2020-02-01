#pragma once

#include <utility>

#include "Operation.h"

class Addition : public Operation {
    ptr<Value> asStrings(const std::string &leftOperand, const std::string &rightOperand) override {
        return make<String>(leftOperand + rightOperand);
    }

    ptr<Value> asIntegers(long long leftOperand, long long rightOperand) override {
        return make<Integer>(leftOperand + rightOperand);
    }

    ptr<Value> asDoubles(double leftOperand, double rightOperand) override {
        return make<Double>(leftOperand + rightOperand);
    }

    ptr<Value> asBooleans(bool leftOperand, bool rightOperand) override {
        return make<Boolean>(leftOperand + rightOperand);
    }
};
