#pragma once

#include "TypeDefinitions.h"

class Object;

struct ExceptionObjects {
    static ptr<Value> null_value(const std::string& message);
    static ptr<Value> bad_cast(const std::string& message);
    static ptr<Value> undefined_operation(const std::string& message);
};