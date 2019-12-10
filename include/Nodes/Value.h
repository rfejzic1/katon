#pragma once

#include "Nodes.h"

struct Value : public Node {
    virtual void asString(std::string& v_string) = 0;
    virtual void asInteger(long long int& v_integer) = 0;
    virtual void asDouble(double& v_double) = 0;
    virtual void asBoolean(bool& v_bool) = 0;
};
