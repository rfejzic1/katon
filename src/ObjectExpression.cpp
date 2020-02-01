#include "../include/AbstractSyntaxTree/ValueExpression/ObjectExpression.h"
#include "../include/AbstractSyntaxTree/Function.h"
#include <utility>


void ObjectExpression::putExpression(const Identifier &ident, Scope scope, ptr<Expression> expression, bool constant) {
    Symbol symbol(ident, constant, scope);
    expressionMap[symbol] = std::move(expression);
}

void ObjectExpression::putFunction(const Identifier &ident, Scope scope, ptr<Function> function) {
    Symbol symbol(ident, false, scope);
    functionMap[symbol] = std::move(function);
}

ptr<Value> ObjectExpression::evaluate(Environment *env) {
    Environment members;
    ptr<Object> object = make<Object>();

    for(auto& it : expressionMap) {
        const Symbol* symbol = &it.first;
        ptr<Value> value = it.second -> evaluate(env);
        members.putValue(symbol->name, symbol->scope, value, symbol->constant);
    }

    for(auto& it : functionMap) {
        const Symbol* symbol = &it.first;
        ptr<Function> function = it.second;
        function -> setOwner(object.get());
        members.putFunction(symbol->name, symbol->scope, function);
    }

    object->setEnvironment(&members);
    return object;
}
