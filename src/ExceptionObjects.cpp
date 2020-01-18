#include "../include/AbstractSyntaxTree/ExceptionObjects.h"

#include "../include/AbstractSyntaxTree/Values/Object.h"
#include "../include/AbstractSyntaxTree/Values/String.h"

ptr<Value> ExceptionObjects::null_value(const std::string &message) {
    return ptr<Value>();
}

ptr<Value> ExceptionObjects::bad_cast(const std::string &message) {
    return ptr<Value>();
}

ptr<Value> ExceptionObjects::undefined_operation(const std::string &message) {
    return ptr<Value>();
}
