#pragma once

#include "Node.h"

struct BinaryOperator : public Node {
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    BinaryOperator() = default;
    BinaryOperator(Node* parent, Node* left, Node* right) : parent(parent), left(left), right(right) {}
};
