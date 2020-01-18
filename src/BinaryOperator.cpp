#include "../include/AbstractSyntaxTree/Operators/BinaryOperator.h"

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
            result = asStrings(left, right);
            break;
        case Type::Object:
            result = asObjects(left, right);
            break;
        case Type::Array:
            result = asArrays(left, right);
            break;
        case Type::Double:
            result = asDoubles(left, right);
            break;
        case Type::Integer:
            result = asIntegers(left, right);
            break;
        case Type::Boolean:
            result = asBooleans(left, right);
            break;
        default:
            break;
    }
    return result;
}

ptr<Value> BinaryOperator::getValue() {
    ptr<Value> leftValue = leftExpression -> getValue();
    ptr<Value> rightValue = rightExpression -> getValue();

    if(!rightValue || !leftValue) {
        ptr<Value> object = ExceptionObjectBuilder()
                .setType("null_value")
                .setMessage("Operands must have a value!")
                .build();
        throw ThrowPacket(object);
    }

    ptr<Value> result = operate(leftValue, rightValue);
    return result;
}

ptr<Value> BinaryOperator::asStrings(ptr<Value> &leftOperand, ptr<Value> &rightOperand) {
    throw ThrowPacket(builder.setMessage("").build());
}

ptr<Value> BinaryOperator::asDoubles(ptr<Value> &leftOperand, ptr<Value> &rightOperand) {
    throw ThrowPacket(builder.setMessage("").build());
}

ptr<Value> BinaryOperator::asIntegers(ptr<Value> &leftOperand, ptr<Value> &rightOperand) {
    throw ThrowPacket(builder.setMessage("").build());
}

ptr<Value> BinaryOperator::asBooleans(ptr<Value> &leftOperand, ptr<Value> &rightOperand) {
    throw ThrowPacket(builder.setMessage("").build());
}

ptr<Value> BinaryOperator::asObjects(ptr<Value> &leftOperand, ptr<Value> &rightOperand) {
    throw ThrowPacket(builder.setMessage("").build());
}

ptr<Value> BinaryOperator::asArrays(ptr<Value> &leftOperand, ptr<Value> &rightOperand) {
    throw ThrowPacket(builder.setMessage("").build());
}

BinaryOperator::BinaryOperator(ptr<Expression> left, ptr<Expression> right) : leftExpression(std::move(left)), rightExpression(std::move(right)) {
    builder.setType("operator_exception");
}
