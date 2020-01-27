#pragma once

#include <utility>

#include "../TypeDefinitions.h"
#include "../StatementBlock.h"
#include "../Expression.h"
#include "../Values/Value.h"
#include "../Environment.h"
#include "../Packets.h"

class WhileStatement : public Statement {
    ptr<Expression> condition;
    ptr<StatementBlock> statementBlock;
public:
    WhileStatement(ptr<Expression> condition, ptr<StatementBlock> statementBlock)
            : condition(condition), statementBlock(statementBlock) { }

    void execute(Environment *env) override {
        Environment local = *env;
        while(condition->evaluate(&local) -> asBoolean()) {
            try {
                statementBlock->execute(&local);
            } catch (BreakPacket &) {
                break;
            } catch (ContinuePacket &) {}
        }
    }
};
