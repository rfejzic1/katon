#include "../include/AbstractSyntaxTree/Operators/Operation.h"

#include "../include/AbstractSyntaxTree/Packets.h"
#include "../include/AbstractSyntaxTree/ExceptionObjects.h"

Type Operation::getGreaterType(ptr<Value> &left, ptr<Value> &right) {
    Type leftType = left -> getType();
    Type rightType = right -> getType();
    return leftType >= rightType ? leftType : rightType;
}

ptr<Value> Operation::getResult(ptr<Value> &left, ptr<Value> &right) {
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

ptr<Value> Operation::asStrings(const std::string &leftOperand, const std::string &rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operation not defined for String type"));
}

ptr<Value> Operation::asDoubles(double leftOperand, double rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operation not defined for Double type"));
}

ptr<Value> Operation::asIntegers(long long int leftOperand, long long int rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operation not defined for Integer type"));
}

ptr<Value> Operation::asBooleans(bool leftOperand, bool rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operation not defined for Boolean type"));
}

ptr<Value> Operation::asObjects(const ptr<Object> &leftOperand, const ptr<Object> &rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operation not defined for Object type"));
}

ptr<Value> Operation::asArrays(const ptr<Array> &leftOperand, const ptr<Array> &rightOperand) {
    throw ThrowPacket(ExceptionObjects::undefined_operation("Operation not defined for Array type"));
}
