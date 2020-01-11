#pragma once

#include <utility>

#include "../TypeDefinitions.h"
#include "../StatementBlock.h"
#include "../Expression.h"
#include "../Values/Value.h"
#include "../Environment.h"

class TryCatchStatement : public Statement {
    Identifier ident;
    ptr<StatementBlock> tryBlock;
    ptr<StatementBlock> catchBlock;
public:
    TryCatchStatement(Identifier ident, ptr<StatementBlock> tryBlock, ptr<StatementBlock> catchBlock)
            : ident(std::move(ident)), tryBlock(std::move(tryBlock)), catchBlock(std::move(catchBlock)) { }

    void execute(Environment *env) override {
        try {
            Environment local = *env;
            tryBlock -> execute(&local);
        } catch(...) {
            Environment local = *env;
            if(!ident.empty())
                ptr<ValueSymbol> catchSymbol = local.getAttribute(ident);
            catchBlock -> execute(&local);
        }
    }
};
