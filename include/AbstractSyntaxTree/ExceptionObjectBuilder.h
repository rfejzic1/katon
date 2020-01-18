#pragma once

#include "TypeDefinitions.h"
#include "Values/Object.h"
#include "Values/String.h"

class ExceptionObjectBuilder {
    std::string messageString = "";
    std::string typeString = "";
public:
    ExceptionObjectBuilder& setMessage(const std::string& message) {
        messageString = message;
        return *this;
    }
    ExceptionObjectBuilder& setType(const std::string& type) {
        typeString = type;
        return *this;
    }
    ptr<Object> build() {
        ptr<Object> object = std::make_shared<Object>();
        ptr<Value> message = std::make_shared<String>(messageString);
        ptr<Value> type = std::make_shared<String>(typeString);
        object -> getEnvironment() -> putAttribute("message", true, message);
        object -> getEnvironment() -> putAttribute("type", true, type);
        return object;
    }
};