#pragma once

#include "Nodes.h"

struct Expression : public Node {

};

// let expr = ((((a + (c * 4)) < b) == true) and (((b + 3) > 0) != false)) or ((d.getAverage()) as Integer)
// let expr = a + c * 4 < b == true and b + 3 > 0 != false or d.getAverage()) as Integer