#pragma once

#include "../Nodes.h"

struct Boolean : public Value {
    bool value = false;

    Boolean() = default;
    Boolean(bool value) : value(value) {}

    void asString(std::string& v_string) override {
        v_string = std::to_string(value);
    }

    void asInteger(long long int& v_integer) override {
        v_integer = value;
    }

    void asDouble(double& v_double) override {
        v_double = value;
    }

    void asBoolean(bool& v_bool) override {
        v_bool = value;
    }
};