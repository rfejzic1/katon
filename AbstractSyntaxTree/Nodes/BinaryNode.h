#pragma once

#include "Node.h"

struct BinaryNode : public Node {
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    BinaryNode() = default;
    BinaryNode(Node* parent, Node* left, Node* right) : parent(parent), left(left), right(right) {}
};
