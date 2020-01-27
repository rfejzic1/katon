#pragma once

#include <utility>

#include "../TypeDefinitions.h"
#include "../StatementBlock.h"
#include "../Expression.h"
#include "../Values/Value.h"
#include "../Environment.h"
#include "../Packets.h"

class TryCatchStatement : public Statement {
    Identifier ident;
    ptr<StatementBlock> tryBlock;
    ptr<StatementBlock> catchBlock;
public:
    TryCatchStatement(Identifier ident, ptr<StatementBlock> tryBlock, ptr<StatementBlock> catchBlock)
            : ident(ident), tryBlock(tryBlock), catchBlock(catchBlock) { }

    void execute(Environment *env) override {
        try {
            Environment local = *env;
            tryBlock -> execute(&local);
        } catch(ThrowPacket& throwPacket) {
            Environment local = *env;
            if(!ident.empty())
                local.putValue(ident, Scope::Public, throwPacket.getValue(), false);
            catchBlock -> execute(&local);
        }
    }
};
