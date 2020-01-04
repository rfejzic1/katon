#pragma once

#include "Primitive.h"

struct String : public Primitive {
    std::string value;

    String() = default;
    String(std::string& value) : value(value) {}

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
};