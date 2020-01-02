#pragma once

#include "../../Nodes.h"

struct Double : public Primitive {
    double value = 0;

    Double() = default;
    Double(double value) : value(value) {}

    std::string asString() override {
        return std::to_string(value);
    }

    long long int asInteger() override {
        return (long long int) value;
    }

    double asDouble() override {
        return value;
    }

    bool asBoolean() override {
        return value != 0;
    }
};