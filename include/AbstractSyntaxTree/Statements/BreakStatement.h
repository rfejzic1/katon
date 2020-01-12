#pragma once

#include "../Statement.h"
#include "../Packets.h"

struct BreakStatement : public Statement {
    void execute(Environment *env) override {
        throw BreakPacket();
    }
};
