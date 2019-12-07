#include <iostream>

#include "Parser.h"
#include "../Common/ParseException.h"


Parser::Parser(const char *filepath) : filepath(filepath) { }

AbstractSyntaxTree Parser::parse() {
    readTokenStream();

    for(Token& token : tokens) {
        std::cout << token.line << " - " << token.lexeme << std::endl;
    }

    return AbstractSyntaxTree();
}

void Parser::error(const char *message) {
    std::cout << "Error: " << message << std::endl;
}

void Parser::log(const char *message) {
    std::cout << "Log: " << message << std::endl;
}

void Parser::readTokenStream() {
    try {
        Klex klex(filepath.c_str());
        tokens.clear();

        while(klex.nextToken()) {
            Token token = klex.getToken();
            tokens.push_back(token);
        }
    } catch (const char* err) {
        throw ParseException(err);
    }
}

