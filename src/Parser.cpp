#include <iostream>
#include <sstream>

#include "../include/Parser.h"

Parser::Parser(const char *filepath) : filepath(filepath), klex(nullptr), astree(nullptr) { }

AbstractSyntaxTree* Parser::parse() {
    openKlex();

    delete astree;
    astree = new AbstractSyntaxTree();
    consume();
    object();

    return astree;
}

Token Parser::token() {
    return currentToken;
}

void Parser::consume(TokenType type, const char* what) {
    if(match(type))
        consume();
    else
        expected(what);
}

void Parser::consume() {
    checkKlex();
    klex->nextToken();
    currentToken = klex->getToken();
    printToken();
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
    std::stringstream msg;
    msg << "Error: " << message;
    throw ParseException(msg.str().c_str());
}

void Parser::log(const char *message) {
    std::cout << "Log: " << message << std::endl;
}

void Parser::printToken() {
    std::cout << "Token " << (int) token().type << " - " << token().lexeme << " on line " << token().line << std::endl;
}

void Parser::unexpected() {
    std::stringstream msg;
    msg << "Unexpected '" << token().lexeme.c_str() << "' on line " << token().line;
    throw ParseException(msg.str().c_str());
}

void Parser::expected(const char* what) {
    std::stringstream msg;
    msg << "Expected " << what << " on line " << token().line;
    throw ParseException(msg.str().c_str());
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

/************************** Productions ******************************/

void Parser::object() {
    consume(TokenType::LeftCurly, "'{'");
    memberDecl();
    consume(TokenType::RightCurly, "'}'");
}

void Parser::memberDecl() {
    while(!match(TokenType::RightCurly)) {
        if(match(TokenType::Public)) {
            consume();
        }else if(match(TokenType::Private)) {
            consume();
        }

        if(matchAny({ TokenType::Let, TokenType::Const, TokenType::Identifier }))
            attributeDecl();
        else if(match(TokenType::Function))
            method();
        else
            unexpected();
    }
}

void Parser::attributeDecl() {
    log("attribute declaration");

    if(matchAny({ TokenType::Let, TokenType::Const }))
        consume();

    consume();
    consume(TokenType::Assign, "assignment operator '='");
    expression();
    consume(TokenType::StatEnd, "';'");
}

void Parser::method() {
    log("method declaration");
    consume();
    consume(TokenType::Identifier, "identifier");
    consume(TokenType::LeftParen, "'('");
    identifierList();
    consume(TokenType::RightParen, "')'");
    statementBlock();
}

void Parser::identifierList() {
    if(!matchAny({TokenType::Identifier, TokenType::Comma}))
        return;

    consume(TokenType::Identifier, "identifier");

    if(match(TokenType::Comma)) {
        consume();
        identifierList();
    }
}

void Parser::statementBlock() {
    consume(TokenType::LeftCurly, "'{'");
    statements();
    consume(TokenType::RightCurly, "'}'");
}

void Parser::statements() {
    while(!match(TokenType::RightCurly))
        statement();
}

void Parser::statement() {
    if(matchAny({ TokenType ::Let, TokenType::Const }))
        variableDecl();
    else if(match(TokenType::If))
        ifStatement();
    else if(match(TokenType::While))
        whileStatement();
    else if(match(TokenType::For))
        forStatement();
    else if(match(TokenType::Try))
        tryCatchStatement();
    else {
        expression();
        consume(TokenType::StatEnd, "';'");
    }
}

void Parser::ifStatement() {
    log("if statement");
    consume();
    expression();
    statementBlock();
}

void Parser::whileStatement() {
    log("while statement");
    consume();
    expression();
    statementBlock();
}

void Parser::forStatement() {
    log("for statement");
    consume();
    consume(TokenType::Identifier, "identifier");
    consume(TokenType::In, "'in'");
    expression();
    statementBlock();
}

void Parser::tryCatchStatement() {
    log("try statement");
    consume();
    statementBlock();
    consume(TokenType::Catch, "'catch'");
    if(match(TokenType::Identifier))
        consume();
    statementBlock();
}

void Parser::otherwiseStatement() {

}

void Parser::variableDecl() {
    log("local variable declaration");
    consume();
    consume(TokenType::Identifier, "identifier");
    consume(TokenType::Assign, "assignment operator '='");
    expression();
    consume(TokenType::StatEnd, "';'");
}

void Parser::expression() {
    consume();
}
