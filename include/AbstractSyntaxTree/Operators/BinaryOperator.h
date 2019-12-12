#pragma once

#include "../../ParseException.h"
#include "../Nodes.h"

struct BinaryOperator : public Expression {
    Node* parent = nullptr;
    Expression* left = nullptr;
    Expression* right = nullptr;

    BinaryOperator() = default;
    BinaryOperator(Node* parent, Expression* left, Expression* right) : parent(parent), left(left), right(right) {}

    void accept(Interpreter interpreter) override {
        if(!left || !right)
            throw ParseException("Operator must have both operands!");
    }
};
