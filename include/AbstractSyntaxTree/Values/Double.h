#pragma once

#include "../Nodes.h"

struct Double : public Value {
    double value = 0;

    Double() = default;
    Double(double value) : value(value) {}

    void asString(std::string& v_string) override {
        v_string = std::to_string(value);
    }

    void asInteger(long long int& v_integer) override {
        v_integer = (long long int) value;
    }

    void asDouble(double& v_double) override {
        v_double = value;
    }

    void asBoolean(bool& v_bool) override {
        v_bool = value != 0;
    }
};