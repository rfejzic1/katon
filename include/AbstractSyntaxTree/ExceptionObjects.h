#pragma once

#include "TypeDefinitions.h"

class ExceptionObjects {
    static ptr<Value> simple_exception(const std::string& type, const std::string& message);
public:
    static ptr<Value> null_value(const std::string& message);
    static ptr<Value> bad_cast(const std::string& message);
    static ptr<Value> undefined_operation(const std::string& message);
    static ptr<Value> undefined(const std::string& message);
    static ptr<Value> call_failed(const std::string& message);
};
