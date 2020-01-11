#pragma once

#include "../Expression.h"
#include "../../RuntimeException.h"
#include "../Type.h"
#include "../Values/Value.h"

struct BinaryOperator : public Expression {
    ptr<Expression> left = nullptr;
    ptr<Expression> right = nullptr;
    BinaryOperator(ptr<Expression>& left, ptr<Expression>& right) : left(left), right(right) {}

    static bool valueIsOfType(ptr<Value>& value, Type type) {
        return value -> getType() == type;
    }

    static void throwIfNotPrimitive(ptr<Value>& value, const char) {
        if(valueIsOfType(value, Type::Object)) {
            throw RuntimeException("Cannot apply operator + to operands of type Object");
        }
        if(valueIsOfType(value, Type::Array)) {
            throw RuntimeException("Cannot apply operator + to operands of type Array");
        }
    }
};
