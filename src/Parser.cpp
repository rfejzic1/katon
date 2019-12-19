#include <iostream>

#include "../include/Parser.h"
#include "../include/ParseException.h"

Parser::Parser(const char *filepath) : filepath(filepath), klex(nullptr), astree(nullptr) { }

AbstractSyntaxTree* Parser::parse() {
    openKlex();

    delete astree;
    astree = new AbstractSyntaxTree();

    object();

    return astree;
}

Token Parser::token() {
    return currentToken;
}

void Parser::consume(TokenType type, const char* message) {
    if(token().type == type)
        consume();
    else
        error(message);
}

void Parser::consume() {
    checkKlex();
    klex->nextToken();
    currentToken = klex->getToken();
}

void Parser::error(const char *message) {
    std::cout << "Error: " << message << std::endl;
    throw ParseException(message);
}

void Parser::log(const char *message) {
    std::cout << "Log: " << message << std::endl;
}

void Parser::openKlex() {
    closeKlex();
    klex = new Klex(filepath.c_str());
}

void Parser::checkKlex() {
    if(!klex)
        throw ParseException("Klex not defined!");
}

void Parser::closeKlex() {
    delete klex;
    klex = nullptr;
}

Parser::~Parser() {
    closeKlex();
}

void Parser::object() {
    switch(token().type) {
        case TokenType::Let:
        case TokenType::Const:
            attributeDecl();
            break;
        case TokenType::Identifier:
            method();
            break;
        default:
            error("Unexpected token...");
    }
}

void Parser::attributeDecl() {
    consume();
    log("Attribute declaration");
    expression();
}

void Parser::method() {
    log("Method declaration");
    consume(TokenType::LeftParen, "Expected '('");
    identifierList();
    consume(TokenType::RightParen, "Expected ')'");
    statementBlock();
}

void Parser::identifierList() {
    if(token().type != TokenType::Identifier && token().type != TokenType::Comma)
        return;

    consume(TokenType::Identifier, "Expected identifier");
    log("Identifier");

    if(token().type == TokenType::Comma) {
        consume();
        identifierList();
    }
}

void Parser::statementBlock() {

}

void Parser::statement() {

}

void Parser::ifStatement() {

}

void Parser::whileStatement() {

}

void Parser::forStatement() {

}

void Parser::tryCatchStatement() {

}

void Parser::otherwiseStatement() {

}

void Parser::variableDecl() {

}

void Parser::expression() {

}
