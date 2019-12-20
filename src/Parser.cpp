#include <iostream>

#include "../include/Parser.h"

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
    if(match(type))
        consume();
    else
        error(message);
}

void Parser::consume() {
    checkKlex();
    klex->nextToken();
    currentToken = klex->getToken();
}

bool Parser::match(TokenType type) {
    return token().type == type;
}

bool Parser::matchAny(const std::vector<TokenType>& types) {
    for(const TokenType& type : types) {
        if(match(type))
            return true;
    }
    return false;
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
        case TokenType::Identifier:
            attributeDecl();
            break;
        case TokenType::Function:
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
    if(matchAny({TokenType::Identifier, TokenType::Comma}))
        return;

    consume(TokenType::Identifier, "Expected identifier");
    log("Identifier");

    if(match(TokenType::Comma)) {
        consume();
        identifierList();
    }
}

void Parser::statementBlock() {
    consume(TokenType::LeftParen, "Expected '{'");
    // todo: statement list??? ; separated???
    consume(TokenType::RightParen, "Expected '}'");
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
