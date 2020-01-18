#pragma once

#include <utility>

#include "../Expression.h"
#include "../Type.h"
#include "../Values/Value.h"
#include "../Packets.h"
#include "../ExceptionObjectBuilder.h"

class BinaryOperator : public Expression {
    ptr<Expression> leftExpression = nullptr;
    ptr<Expression> rightExpression = nullptr;
    ExceptionObjectBuilder builder;

    static Type getGreaterType(ptr<Value>& left, ptr<Value>& right);
    ptr<Value> operate(ptr<Value>& left, ptr<Value>& right);
public:
    BinaryOperator(ptr<Expression> left, ptr<Expression> right);
    virtual ptr<Value> asStrings(ptr<Value>& leftOperand, ptr<Value>& rightOperand);
    virtual ptr<Value> asDoubles(ptr<Value>& leftOperand, ptr<Value>& rightOperand);
    virtual ptr<Value> asIntegers(ptr<Value>& leftOperand, ptr<Value>& rightOperand);
    virtual ptr<Value> asBooleans(ptr<Value>& leftOperand, ptr<Value>& rightOperand);
    virtual ptr<Value> asObjects(ptr<Value>& leftOperand, ptr<Value>& rightOperand);
    virtual ptr<Value> asArrays(ptr<Value>& leftOperand, ptr<Value>& rightOperand);
    ptr<Value> getValue() override;
};
