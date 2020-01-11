#pragma once

#include "../TypeDefinitions.h"
#include "../StatementBlock.h"
#include "../Expression.h"
#include "../Values/Value.h"
#include "../Environment.h"
#include "../Iterable.h"
#include "../../RuntimeException.h"
#include "../Iterator.h"

class ForStatement : public Statement {
    Identifier ident;
    ptr<Expression> expression;
    ptr<StatementBlock> statementBlock;
public:
    ForStatement(Identifier& ident, ptr<Expression>& expression, ptr<StatementBlock>& statementBlock)
    : ident(ident), expression(expression), statementBlock(statementBlock) { }

    void execute(Environment *env) override {
        ptr<Value> expressionResult = expression -> getValue();
        ptr<Iterable> iterable = std::dynamic_pointer_cast<Iterable>(expressionResult);

        if(!iterable)
            throw RuntimeException("Given value is not an iterable");

        Iterator iterator(iterable -> getValues());

        while(iterator.hasNext()) {
            Environment local = *env;
            ptr<Value> newValue = iterator.next();
            local.putAttribute(ident, false, newValue);
            statementBlock -> execute(env);
        }
    }
};
