#pragma once

#include "Nodes.h"
#include "Values/Value.h"

class Value;

struct Expression : public Node {
    virtual ptr<Value> getValue() = 0;
};
