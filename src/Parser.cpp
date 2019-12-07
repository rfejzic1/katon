#include <iostream>

#include "../include/Parser.h"
#include "../include/ParseException.h"

Parser::Parser(const char *filepath) : filepath(filepath), klex(nullptr), astree(nullptr) { }

AbstractSyntaxTree* Parser::parse() {
    openKlex();

    delete astree;
    astree = new AbstractSyntaxTree();

    return astree;
}

void Parser::consume(TokenType) {

}

void Parser::error(const char *message) {
    std::cout << "Error: " << message << std::endl;
}

void Parser::log(const char *message) {
    std::cout << "Log: " << message << std::endl;
}

void Parser::openKlex() {
    closeKlex();
    klex = new Klex(filepath.c_str());
}

void Parser::closeKlex() {
    delete klex;
}

Parser::~Parser() {
    closeKlex();
}