#pragma once

#include <vector>

#include "Node.h"

struct NaryNode {
    std::vector<Node*> nodes;

    void add(Node* node) {
        nodes.push_back(node);
    }
};
