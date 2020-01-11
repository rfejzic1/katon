#pragma once

#include "../TypeDefinitions.h"
#include "../StatementBlock.h"
#include "../Expression.h"
#include "../Values/Value.h"
#include "../Environment.h"

class WhileStatement : public Statement {
    ptr<Expression> condition;
    ptr<StatementBlock> statementBlock;
public:
    WhileStatement(ptr<Expression>& condition, ptr<StatementBlock>& statementBlock)
            : condition(condition), statementBlock(statementBlock) { }

    void execute(Environment *env) override {
        Environment local = *env;
        while(condition -> getValue() -> asBoolean()) {
            statementBlock -> execute(&local);
        }
    }
};
