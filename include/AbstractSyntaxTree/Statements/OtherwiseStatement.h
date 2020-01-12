#pragma once

#include <utility>

#include "../TypeDefinitions.h"
#include "../StatementBlock.h"
#include "../Expression.h"
#include "../Values/Value.h"
#include "../Environment.h"
#include "../Packets.h"

class OtherwiseStatement : public Statement {
    ptr<Statement> statement;
    ptr<StatementBlock> statementBlock;
public:
    OtherwiseStatement(ptr<Statement> statement , ptr<StatementBlock> statementBlock)
            : statement(std::move(statement)), statementBlock(std::move(statementBlock)) { }

    void execute(Environment *env) override {
        try {
            statement -> execute(env);
        } catch(ThrowPacket&) {
            Environment local = *env;
            statementBlock -> execute(&local);
        }
    }
};
