#pragma once

#include <utility>

#include "BinaryOperator.h"

struct Disjunction : public BinaryOperator {
    ptr<Value> asIntegers(long long leftOperand, long long rightOperand) override {
        return make<Integer>(leftOperand || rightOperand);
    }

    ptr<Value> asDoubles(double leftOperand, double rightOperand) override {
        return make<Double>((bool) leftOperand || (bool) rightOperand);
    }

    ptr<Value> asBooleans(bool leftOperand, bool rightOperand) override {
        return make<Boolean>(leftOperand || rightOperand);
    }
public:
    Disjunction(ptr<Expression> left, ptr<Expression> right) : BinaryOperator(std::move(left), std::move(right)) { }
};
