#pragma once

#include "Value.h"

struct Integer : public Value {
    long long int value = 0;

    Integer() = default;
    Integer(long long int value) : value(value) {}

    std::string asString() override {
        return std::to_string(value);
    }

    long long int asInteger() override {
        return value;
    }

    double asDouble() override {
        return (double) value;
    }

    bool asBoolean() override {
        return value != 0;
    }

    Type getType() override {
        return Type::Integer;
    }
};