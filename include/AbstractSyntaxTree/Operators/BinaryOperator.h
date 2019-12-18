#pragma once

#include "../../ParseException.h"
#include "../Nodes.h"

struct BinaryOperator : public Expression {
    ptr<Node> parent = nullptr;
    ptr<Expression> left = nullptr;
    ptr<Expression> right = nullptr;

    BinaryOperator() = default;
    BinaryOperator(Node* parent, Expression* left, Expression* right) : parent(parent), left(left), right(right) {}

    void accept(Interpreter interpreter) override {}
};
