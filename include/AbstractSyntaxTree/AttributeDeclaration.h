#pragma once

#include "Nodes.h"

struct AttributeDeclaration : public Node {
    Symbol* symbol;
    Expression* expression;

    void accept(Interpreter interpreter) override {
        //
    }
};