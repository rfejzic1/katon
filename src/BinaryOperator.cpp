#include "../include/AbstractSyntaxTree/Operators/BinaryOperator.h"

#include "../include/AbstractSyntaxTree/Values/Object.h"
#include "../include/AbstractSyntaxTree/Values/Array.h"

BinaryOperator::BinaryOperator(ptr<Expression> left, ptr<Expression> right)
    : leftExpression(std::move(left)), rightExpression(std::move(right)) { }

Type BinaryOperator::getGreaterType(ptr<Value> &left, ptr<Value> &right) {
    Type leftType = left -> getType();
    Type rightType = right -> getType();
    return leftType >= rightType ? leftType : rightType;
}

ptr<Value> BinaryOperator::operate(ptr<Value> &left, ptr<Value> &right) {
    ptr<Value> result;
    Type type = getGreaterType(left, right);

    switch(type) {
        case Type::String:
            result = asStrings(left -> asString(), right -> asString());
            break;
        case Type::Object:
            result = asObjects(left -> asObject(), right -> asObject());
            break;
        case Type::Array:
            result = asArrays(left -> asArray(), right -> asArray());
            break;
        case Type::Double:
            result = asDoubles(left -> asDouble(), right -> asDouble());
            break;
        case Type::Integer:
            result = asIntegers(left -> asInteger(), right -> asInteger());
            break;
        case Type::Boolean:
            result = asBooleans(left -> asBoolean(), right -> asBoolean());
            break;
        default:
             throw ThrowPacket(ExceptionObjects::undefined_operation("Types are not operable!"));
    }
    return result;
}

ptr<Value> BinaryOperator::getValue() {
    ptr<Value> leftValue = leftExpression -> getValue();
    ptr<Value> rightValue = rightExpression -> getValue();

    if(!rightValue || !leftValue) {
        ptr<Value> object = ExceptionObjects::null_value("Both operands must have a value");
        throw ThrowPacket(object);
    }

    ptr<Value> result = operate(leftValue, rightValue);
    return result;
}

ptr<Value> BinaryOperator::asStrings(const std::string &leftOperand, const std::string &rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operator not defined for String type"));
}

ptr<Value> BinaryOperator::asDoubles(double leftOperand, double rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operator not defined for Double type"));
}

ptr<Value> BinaryOperator::asIntegers(long long int leftOperand, long long int rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operator not defined for Integer type"));
}

ptr<Value> BinaryOperator::asBooleans(bool leftOperand, bool rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operator not defined for Boolean type"));
}

ptr<Value> BinaryOperator::asObjects(const ptr<Object> &leftOperand, const ptr<Object> &rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operator not defined for Object type"));
}

ptr<Value> BinaryOperator::asArrays(const ptr<Array> &leftOperand, const ptr<Array> &rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operator not defined for Array type"));
}
