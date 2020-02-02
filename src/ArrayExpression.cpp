#include "../include/AbstractSyntaxTree/ValueExpression/ArrayExpression.h"

#include "../include/AbstractSyntaxTree/Packets.h"
#include "../include/AbstractSyntaxTree/Values/Array.h"

ptr<Value> ArrayExpression::evaluate(Environment *env) {
    ValueList valueList;
    for(auto& element : *elements) {
        ptr<Value> value = element->evaluate(env);
        valueList.push_back(value);
    }
    return make<Array>(valueList);
}

ArrayExpression::ArrayExpression() {
    elements = make<ExpressionList>();
}

ArrayExpression::ArrayExpression(const ExpressionList& expressionList)
    : elements(make<ExpressionList>(expressionList)) {}
