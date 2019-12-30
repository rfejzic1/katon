#include <iostream>
#include <sstream>

#include "../include/Parser.h"

Parser::Parser(const char *filepath) : filepath(filepath), klex(nullptr), astree(nullptr) { }

AbstractSyntaxTree* Parser::parse() {
    openKlex();

    delete astree;
    astree = new AbstractSyntaxTree();

    consume();
    module();

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
    std::cout << "Token "
        << (int) token().type << " - "
        << token().lexeme << " on line "
        << token().line << " column "
        << token().col << std::endl;
}

void Parser::unexpected() {
    std::stringstream msg;
    msg << "Unexpected '" << token().lexeme.c_str() << "' on line " << token().line << " column " << token().col;
    throw ParseException(msg.str().c_str());
}

void Parser::expected(const char* what) {
    std::stringstream msg;
    msg << "Expected " << what << " on line " << token().line << " column " << token().col;
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

void Parser::module() {
    while(!match(TokenType::EndOfFile)) {
        memberDecl();
    }
}

void Parser::object() {
    consume(TokenType::LeftCurly, "'{'");
    while(!match(TokenType::RightCurly) && !match(TokenType::EndOfFile)) {
        memberDecl();
    }
    consume(TokenType::RightCurly, "'}'");
}

void Parser::array() {
    consume(TokenType::LeftBrack, "'['");
    expressionList();
    consume(TokenType::RightBrack, "']'");
}

void Parser::memberDecl() {
    if(match(TokenType::Public)) {
        consume();
    } else if(match(TokenType::Private)) {
        consume();
    }

    if(matchAny({ TokenType::Let, TokenType::Const, TokenType::Identifier }))
        attributeDecl();
    else if(match(TokenType::Function))
        method();
    else {
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

void Parser::expressionList() {
    if(!match(TokenType::RightParen)) {
        expression();
        while(match(TokenType::Comma)) {
            consume();
            expressionList();
        }
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
        localDecl();
    else if(match(TokenType::If))
        ifStatement();
    else if(match(TokenType::While))
        whileStatement();
    else if(match(TokenType::For))
        forStatement();
    else if(match(TokenType::Try))
        tryCatchStatement();
    else if(match(TokenType::Continue))
        continueStatement();
    else if(match(TokenType::Break))
        breakStatement();
    else if(match(TokenType::Throw))
        throwStatement();
    else if(match(TokenType::Return))
        returnStatement();
    else {
        expression();
        if(match(TokenType::Otherwise)) {
            otherwiseStatement();
        }
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
    consume();
    statementBlock();
}

void Parser::continueStatement() {
    consume();
    consume(TokenType::StatEnd, "';'");
}

void Parser::breakStatement() {
    consume();
    consume(TokenType::StatEnd, "';'");
}

void Parser::returnStatement() {
    consume();
    if(!match(TokenType::StatEnd)) {
        expression();
    }
    consume(TokenType::StatEnd, "';'");
}

void Parser::throwStatement() {
    consume();
    expression();
    consume(TokenType::StatEnd, "';'");
}

void Parser::localDecl() {
    log("local variable declaration");
    consume();
    consume(TokenType::Identifier, "identifier");
    consume(TokenType::Assign, "assignment operator '='");
    expression();
    consume(TokenType::StatEnd, "';'");
}

void Parser::expression() {
    log("expression");
    logOr();
    if(matchAny({ TokenType::Assign, TokenType::PlusAssign, TokenType::MultAssign, TokenType::MinusAssign, TokenType::DivAssign, TokenType::ExpAssign, TokenType::ModAssign })) {
        consume();
        logOr();
    }
}

void Parser::logOr() {
    log("or");
    logAnd();
    while(match(TokenType::Or)) {
        consume();
        logAnd();
    }
}

void Parser::logAnd() {
    log("and");
    equality();
    while(match(TokenType::And)) {
        consume();
        equality();
    }
}

void Parser::equality() {
    log("equality");
    comparison();
    while(matchAny({ TokenType::NotEqu, TokenType::Equals })) {
        consume();
        comparison();
    }
}

void Parser::comparison() {
    log("comparison");
    term();
    while(matchAny({ TokenType::LThan, TokenType::LThanEqu, TokenType::GThan, TokenType::GThanEqu })) {
        consume();
        term();
    }
}

void Parser::term() {
    log("term");
    factor();
    while(matchAny({ TokenType::Plus, TokenType::Minus })) {
        consume();
        factor();
    }
}

void Parser::factor() {
    log("factor");
    unary();
    while(matchAny({ TokenType::Mult, TokenType::Div, TokenType::Mod, TokenType::Exp })) {
        consume();
        unary();
    }
}

void Parser::unary() {
    log("unary");
    while(match(TokenType::Neg))
        consume();
    primary();

    // todo: cast here?
}

void Parser::primary() {
    if(match(TokenType::Identifier)) {
        variable(nullptr);
    } else if(match(TokenType::LeftParen)) {
        log("grouping");
        consume(TokenType::LeftParen, "'('");
        expression();
        consume(TokenType::RightParen, "')'");
    } else {
        value();
    }
}

void Parser::value() {
    if(matchAny({ TokenType::True, TokenType::False })) {
        log("Boolean");
        consume();
    } else if(match(TokenType::Number)) {
        log("Number");
        consume();
    } else if(match(TokenType::SingleQuote)) {
        log("String");
        consume();
        consume(TokenType::String, "string");
        consume(TokenType::SingleQuote, "\"'\"");
    } else if(match(TokenType::DoubleQuote)) {
        log("String");
        consume();
        consume(TokenType::String, "string");
        consume(TokenType::DoubleQuote, "'\"'");
    } else if(match(TokenType::LeftCurly)) {
        object();
    } else if(match(TokenType::LeftBrack)) {
        array();
    } else if(match(TokenType::Lambda)) {
        lambda();
    } else {
        unexpected();
    }
}

void Parser::lambda() {
    consume();
    consume(TokenType::LeftParen, "'('");
    identifierList();
    consume(TokenType::RightParen, "')'");
    statementBlock();
}

void Parser::variable(Expression* callee) {
    log("Variable");
    consume(TokenType::Identifier, "identifier");
    postfix(callee);
}

void Parser::postfix(Expression* callee) {
    if(match(TokenType::LeftParen)) {
        call(callee);
    } else if(match(TokenType::LeftBrack)) {
        access(callee);
    } else if(match(TokenType::Dot)) {
        consume();
        variable(callee);
    }
}

void Parser::call(Expression* callee) {
    consume();
    expressionList();
    consume(TokenType::RightParen, "')'");
    postfix(callee);
}

void Parser::access(Expression* callee) {
    consume();
    expression();
    consume(TokenType::RightBrack, "']'");
    postfix(callee);
}
