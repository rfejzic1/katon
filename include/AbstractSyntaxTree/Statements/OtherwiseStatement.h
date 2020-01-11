#pragma once

#include "../TypeDefinitions.h"
#include "../StatementBlock.h"
#include "../Expression.h"
#include "../Values/Value.h"
#include "../Environment.h"

class Otherwise : public Statement {
    ptr<Statement> statement;
    ptr<StatementBlock> statementBlock;
public:
    Otherwise(ptr<Statement>& statement , ptr<StatementBlock>& statementBlock)
            : statement(statement), statementBlock(statementBlock) { }

    void execute(Environment *env) override {
        try {
            statement -> execute(env);
        } catch(...) {
            Environment local = *env;
            statementBlock -> execute(&local);
        }
    }
};
