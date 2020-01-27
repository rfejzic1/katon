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
    ptr<Expression> leftExpression;
    ptr<Expression> rightExpression;

    static Type getGreaterType(ptr<Value>& left, ptr<Value>& right);
    ptr<Value> operate(ptr<Value>& left, ptr<Value>& right);

protected:
    virtual ptr<Value> asStrings(const std::string &leftOperand, const std::string &rightOperand);
    virtual ptr<Value> asDoubles(double leftOperand, double rightOperand);
    virtual ptr<Value> asIntegers(long long int leftOperand, long long int rightOperand);
    virtual ptr<Value> asBooleans(bool leftOperand, bool rightOperand);
    virtual ptr<Value> asObjects(const ptr<Object> &leftOperand, const ptr<Object> &rightOperand);
    virtual ptr<Value> asArrays(const ptr<Array> &leftOperand, const ptr<Array> &rightOperand);

public:
    BinaryOperator(ptr<Expression> left, ptr<Expression> right);
    ptr<Value> evaluate(Environment* env) override;
};
