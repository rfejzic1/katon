#pragma once

#include <utility>

#include "Values/Value.h"

struct BreakPacket {};

struct ContinuePacket {};

class CarrierPacket {
    ptr<Value> value;
public:
    explicit CarrierPacket(ptr<Value> value) : value(std::move(value)) { }
    ptr<Value> getValue() {
        return value;
    }
};

struct ReturnPacket : public CarrierPacket {
    explicit ReturnPacket(ptr<Value> value) : CarrierPacket(std::move(value)) { }
};

struct ThrowPacket : public CarrierPacket {
    explicit ThrowPacket(ptr<Value> value) : CarrierPacket(std::move(value)) { }
};
