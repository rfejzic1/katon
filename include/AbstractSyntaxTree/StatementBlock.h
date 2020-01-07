#pragma once

#include <vector>

#include "../Interpreter.h"
#include "./Expression.h"
#include "./Statement.h"

class StatementBlock : public Executable {
    std::vector<ptr<Statement>> statements;
public:
    void execute(Interpreter* interpreter) override {
        for(ptr<Statement>& statement : statements) {
            statement -> execute(interpreter);
        }
    }
};
