#include "../include/AbstractSyntaxTree/ObjectDescriptor.h"

#include <utility>

void ObjectDescriptor::putExpression(const Identifier &ident, Scope scope, ptr<Expression> expression, bool constant) {
    Symbol symbol(ident, constant, scope);
    expressionMap[symbol] = std::move(expression);
}

void ObjectDescriptor::putFunction(const Identifier &ident, Scope scope, ptr<Function> function) {
    Symbol symbol(ident, false, scope);
    functionMap[symbol] = std::move(function);
}

ptr<Value> ObjectDescriptor::evaluate(Environment *env) {
    Environment members;

    for(auto& it : expressionMap) {
        const Symbol* symbol = &it.first;
        ptr<Value> value = it.second -> evaluate(env);
        members.putValue(symbol->name, symbol->scope, value, symbol->constant);
    }

    for(auto& it : functionMap) {
        const Symbol* symbol = &it.first;
        ptr<Function> function = it.second;
        members.putFunction(symbol->name, symbol->scope, function);
    }

    return make<Object>(members);
}
