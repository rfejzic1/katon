#include "../include/AbstractSyntaxTree/ValueExpression/ArrayExpression.h"

#include "../include/AbstractSyntaxTree/Packets.h"
#include "../include/AbstractSyntaxTree/Values/String.h"

ptr<Value> ArrayExpression::evaluate(Environment *env) {
    throw ThrowPacket(make<String>("Array not yet implemented :("));
}

ArrayExpression::ArrayExpression() {
    elements = make<ExpressionList>();
}

ArrayExpression::ArrayExpression(const ExpressionList& expressionList)
    : elements(make<ExpressionList>(expressionList)) {}
