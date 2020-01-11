#pragma once

#include "../TypeDefinitions.h"
#include "../StatementBlock.h"
#include "../Expression.h"
#include "../Values/Value.h"

class IfStatement : public Statement{
    ptr<Expression> condition;
    ptr<StatementBlock> trueBlock;
    ptr<StatementBlock> falseBlock;
public:
    IfStatement(ptr<Expression>& condition, ptr<StatementBlock>& trueBlock, ptr<StatementBlock>& falseBlock)
        : condition(condition), trueBlock(trueBlock), falseBlock(falseBlock) { }

    void execute(Environment *env) override {
        bool conditionTrue = condition -> getValue() -> asBoolean();

        if(conditionTrue) {
            trueBlock -> execute(env);
        } else {
            falseBlock -> execute(env);
        }
    }
};