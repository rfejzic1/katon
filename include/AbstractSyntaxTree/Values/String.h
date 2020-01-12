#pragma once

#include <utility>

#include "Value.h"

struct String : public Value {
    std::string value;

    String() = default;
    explicit String(std::string  value) : value(std::move(value)) {}

    std::string asString() override {
        return value;
    }

    long long int asInteger() override {
        return std::stoll(value);
    }

    double asDouble() override {
        return std::stod(value);
    }

    bool asBoolean() override {
        return !value.empty();
    }

    Type getType() override {
        return Type::String;
    }
};