#include "../include/AbstractSyntaxTree/Operators/BinaryOperator.h"

#include <utility>

#include "../include/AbstractSyntaxTree/ExceptionObjects.h"
#include "../include/AbstractSyntaxTree/Packets.h"

BinaryOperator::BinaryOperator(ptr<Operation> operation, ptr<Expression> left, ptr<Expression> right)
    : operation(std::move(operation)), leftExpression(std::move(left)), rightExpression(std::move(right)) { }

ptr<Value> BinaryOperator::evaluate(Environment* env) {
    ptr<Value> leftValue = leftExpression->evaluate(env);
    ptr<Value> rightValue = rightExpression->evaluate(env);

    ptr<Value> result = operation -> getResult(leftValue, rightValue);
    return result;
}
