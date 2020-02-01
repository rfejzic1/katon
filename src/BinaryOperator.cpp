#include "../include/AbstractSyntaxTree/Operators/BinaryOperator.h"

#include <utility>

#include "../include/AbstractSyntaxTree/ExceptionObjects.h"
#include "../include/AbstractSyntaxTree/Packets.h"

BinaryOperator::BinaryOperator(ptr<Operation> operation, ptr<Expression> left, ptr<Expression> right)
    : operation(std::move(operation)), leftExpression(std::move(left)), rightExpression(std::move(right)) { }

ptr<Value> BinaryOperator::evaluate(Environment* env) {
    ptr<Value> leftValue = leftExpression->evaluate(env);
    ptr<Value> rightValue = rightExpression->evaluate(env);

    if(!rightValue || !leftValue) {
        ptr<Value> object = ExceptionObjects::null_value("Both operands must have a value");
        throw ThrowPacket(object);
    }

    ptr<Value> result = operation -> getResult(leftValue, rightValue);
    return result;
}
