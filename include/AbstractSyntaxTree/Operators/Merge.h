#pragma once

#include <utility>

#include "Operation.h"

class Merge : public Operation {
    ptr<Value> asObjects(const ptr<Object> &leftOperand, const ptr<Object> &rightOperand) override {
        leftOperand -> getEnvironment() -> merge(rightOperand -> getEnvironment());
        return leftOperand;
    }
};
