#pragma once

#include <vector>

#include "./Statement.h"

class StatementBlock : public Statement {
    std::vector<ptr<Statement>> statements;
public:
    explicit StatementBlock(std::vector<ptr<Statement>> statements) : statements(statements) { }
    void execute(Environment* env) override {
        for(ptr<Statement>& statement : statements) {
            statement -> execute(env);
        }
    }
};
