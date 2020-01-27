#pragma once

#include "unordered_map"

#include "Expression.h"
#include "Values/Object.h"

class ObjectDescriptor : public Expression {
    std::unordered_map<Symbol, ptr<Expression>, SymbolHashFunction> expressionMap;
    std::unordered_map<Symbol, ptr<Function>, SymbolHashFunction> functionMap;
public:
    explicit ObjectDescriptor() = default;

    void putExpression(const Identifier &ident, Scope scope, ptr<Expression> expression, bool constant);
    void putFunction(const Identifier& ident, Scope scope, ptr<Function> function);

    ptr<Value> evaluate(Environment* env) override;
};
