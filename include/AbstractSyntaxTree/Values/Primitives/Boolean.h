#pragma once

#include "Primitive.h"

struct Boolean : public Primitive {
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
};