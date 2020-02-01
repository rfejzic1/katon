#include "../include/AbstractSyntaxTree/ExceptionObjects.h"

#include "../include/AbstractSyntaxTree/Values/String.h"
#include "../include/AbstractSyntaxTree/ObjectBuilder.h"

ptr<Value> ExceptionObjects::simple_exception(const std::string &type, const std::string &message) {
    ObjectBuilder builder;
    builder.putAttribute("type", true, make<String>(type));
    builder.putAttribute("message", true, make<String>(message));
    return builder.build();
}

ptr<Value> ExceptionObjects::null_value(const std::string &message) {
    return simple_exception("null_value", message);
}

ptr<Value> ExceptionObjects::bad_cast(const std::string &message) {
    return simple_exception("bad_cast", message);
}

ptr<Value> ExceptionObjects::undefined_operation(const std::string &message) {
    return simple_exception("undefined_operation", message);
}

ptr<Value> ExceptionObjects::undefined(const std::string &message) {
    return simple_exception("undefined", message);
}

ptr<Value> ExceptionObjects::call_failed(const std::string &message) {
    return simple_exception("call_failed", message);
}
