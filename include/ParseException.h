#pragma once

#include <exception>

class ParseException : public std::runtime_error {
public:
    explicit ParseException(const char *message) : runtime_error(message) {}
};
