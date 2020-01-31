#pragma once

#include <utility>

#include "BinaryOperator.h"

class Addition : public BinaryOperator {
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
public:
    Addition(ptr<Expression> left, ptr<Expression> right) : BinaryOperator(std::move(left), std::move(right)) { }
};
