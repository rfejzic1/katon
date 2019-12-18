#pragma once

#include "Nodes.h"
#include "Values/Value.h"

class Value;

struct Expression : public Node {
    virtual ptr<Value> getValue() = 0;
};

// let expr = ((((a + (c * 4)) < b) == true) and (((b + 3) > 0) != false)) or ((d.getAverage()) as Integer)
// let expr = a + c * 4 < b == true and b + 3 > 0 != false or d.getAverage()) as Integer