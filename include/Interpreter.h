#pragma once

#include "./AbstractSyntaxTree/Values/Object.h"
#include "./AbstractSyntaxTree/TypeDefinitions.h"

class Interpreter {
    ptr<Object> object;
public:
    explicit Interpreter(ptr<Object> object) : object(object) {}
    void execute();
};
