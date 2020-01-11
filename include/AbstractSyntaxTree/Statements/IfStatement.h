#pragma once

#include <utility>

#include "../TypeDefinitions.h"
#include "../StatementBlock.h"
#include "../Expression.h"
#include "../Values/Value.h"
#include "../Environment.h"

class IfStatement : public Statement {
    ptr<Expression> condition;
    ptr<StatementBlock> trueBlock;
    ptr<StatementBlock> falseBlock;
public:
    IfStatement(ptr<Expression> condition, ptr<StatementBlock> trueBlock, ptr<StatementBlock> falseBlock)
        : condition(std::move(condition)), trueBlock(std::move(trueBlock)), falseBlock(std::move(falseBlock)) { }

    void execute(Environment *env) override {
        bool conditionTrue = condition -> getValue() -> asBoolean();
        Environment local = *env;

        if(conditionTrue) {
            trueBlock -> execute(&local);
        } else {
            falseBlock -> execute(&local);
        }
    }
};
