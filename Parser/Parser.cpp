#include <iostream>
#include "Parser.h"

Parser::Parser(const char *filepath) : filepath(filepath) { }

AbstractSyntaxTree Parser::parse() {
    return AbstractSyntaxTree();
}

void Parser::error(const char *message) {
    std::cout << "Error: " << message << std::endl;
}

void Parser::log(const char *message) {
    std::cout << "Warning: " << message << std::endl;
}

