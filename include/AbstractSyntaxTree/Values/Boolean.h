#pragma once

#include "Value.h"

struct Boolean : public Value {
    bool value = false;

    Boolean() = default;
    Boolean(bool value) : value(value) {}

    std::string asString() override {
        return std::to_string(value);
    }

    long long int asInteger() override {
        return value;
    }

    double asDouble() override {
        return value;
    }

    bool asBoolean() override {
        return value;
    }

    Type getType() override {
        return Type::Boolean;
    }
};