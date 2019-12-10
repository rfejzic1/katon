#pragma once

#include "../Nodes.h"

struct String : public Value {
    std::string value;

    String() = default;
    String(std::string& value) : value(value) {}

    void asString(std::string& v_string) override {
        v_string = value;
    }

    void asInteger(long long int& v_integer) override {
        v_integer = std::stoll(value);
    }

    void asDouble(double& v_double) override {
        v_double = std::stod(value);
    }

    void asBoolean(bool& v_bool) override {
        v_bool = !value.empty();
    }
};