#pragma once

#include <exception>

class ParseException : public std::exception {
    const char* message;
public:
    ParseException(const char* message) : message(message) {}

    const char * what () const throw() override {
        return message;
    }
};
