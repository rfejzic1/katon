#pragma once

#include <utility>

#include "../Expression.h"
#include "../Type.h"

#include "../Values/String.h"
#include "../Values/Integer.h"
#include "../Values/Boolean.h"
#include "../Values/Double.h"
#include "../Values/Object.h"
#include "../Values/Array.h"

class BinaryOperator : public Expression {
    ptr<Expression> leftExpression = nullptr;
    ptr<Expression> rightExpression = nullptr;

    static Type getGreaterType(ptr<Value>& left, ptr<Value>& right);
    ptr<Value> operate(ptr<Value>& left, ptr<Value>& right);
public:
    BinaryOperator(ptr<Expression> left, ptr<Expression> right);
    virtual ptr<Value> asStrings(const std::string &leftOperand, const std::string &rightOperand);
    virtual ptr<Value> asDoubles(double leftOperand, double rightOperand);
    virtual ptr<Value> asIntegers(long long int leftOperand, long long int rightOperand);
    virtual ptr<Value> asBooleans(bool leftOperand, bool rightOperand);
    virtual ptr<Value> asObjects(const ptr<Object> &leftOperand, const ptr<Object> &rightOperand);
    virtual ptr<Value> asArrays(const ptr<Array> &leftOperand, const ptr<Array> &rightOperand);
    ptr<Value> getValue() override;
};
