#pragma once

#include "../Statement.h"
#include "../Packets.h"

struct ContinueStatement : public Statement {
    void execute(Environment *env) override {
        throw ContinuePacket();
    }
};
