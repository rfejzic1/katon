#pragma once

#include <exception>
#include <stdexcept>

class RuntimeException : public std::runtime_error {
public:
    explicit RuntimeException(const char *message) : runtime_error(message) {}
};
