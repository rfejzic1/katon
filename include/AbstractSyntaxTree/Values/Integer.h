#pragma once

#include "../Nodes.h"

struct Integer : public Value {
    long long int value = 0;

    Integer() = default;
    Integer(long long int value) : value(value) {}

    void asString(std::string& v_string) override {
        v_string = std::to_string(value);
    }

    void asInteger(long long int& v_integer) override {
        v_integer = value;
    }

    void asDouble(double& v_double) override {
        v_double = (double) value;
    }

    void asBoolean(bool& v_bool) override {
        v_bool = value;
    }
};