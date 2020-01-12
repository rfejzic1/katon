#include <iostream>
#include <sstream>

#include "../include/Parser.h"
#include "../include/AbstractSyntaxTree/ValueSymbol.h"
#include "../include/AbstractSyntaxTree/Function.h"
#include "../include/AbstractSyntaxTree/Values/Object.h"
#include "../include/AbstractSyntaxTree/Expression.h"
#include "../include/AbstractSyntaxTree/TypeDefinitions.h"
#include "../include/AbstractSyntaxTree/Values/Array.h"
#include "../include/AbstractSyntaxTree/StatementBlock.h"
#include "../include/AbstractSyntaxTree/Statements/IfStatement.h"
#include "../include/AbstractSyntaxTree/Statements/WhileStatement.h"
#include "../include/AbstractSyntaxTree/Statements/ForStatement.h"
#include "../include/AbstractSyntaxTree/Statements/TryCatchStatement.h"
#include "../include/AbstractSyntaxTree/Statements/ContinueStatement.h"
#include "../include/AbstractSyntaxTree/Statements/BreakStatement.h"
#include "../include/AbstractSyntaxTree/Statements/ReturnStatement.h"
#include "../include/AbstractSyntaxTree/Statements/ThrowStatement.h"
#include "../include/AbstractSyntaxTree/Values/String.h"
#include "../include/AbstractSyntaxTree/Statements/ExpressionStatement.h"
#include "../include/AbstractSyntaxTree/Statements/OtherwiseStatement.h"

Parser::Parser(const char *filepath) : filepath(filepath), klex(nullptr) { }

Object* Parser::parse() {
    openKlex();

    consume();
    ptr<Object> moduleObject = module();

    return moduleObject.get();
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

ptr<Object> Parser::module() {
    ptr<Object> object(new Object());
    while(!match(TokenType::EndOfFile)) {
        memberDecl(object);
    }
    return object;
}

ptr<Object> Parser::object() {
    ptr<Object> object(new Object());

    consume(TokenType::LeftCurly, "'{'");
    while(!match(TokenType::RightCurly) && !match(TokenType::EndOfFile)) {
        memberDecl(object);
    }
    consume(TokenType::RightCurly, "'}'");

    return object;
}

ptr<Array> Parser::array() {
    consume(TokenType::LeftBrack, "'['");
    expressionList();
    consume(TokenType::RightBrack, "']'");
}

void Parser::memberDecl(ptr<Object>& object) {
    Scope scope = Scope::Public;

    if(match(TokenType::Public)) {
        consume();
    } else if(match(TokenType::Private)) {
        scope = Scope::Private;
        consume();
    }

    if(matchAny({ TokenType::Let, TokenType::Const, TokenType::Identifier }))
        attributeDecl(object, scope);
    else if(match(TokenType::Function))
        method(object, scope);
    else {
        unexpected();
    }
}

void Parser::attributeDecl(ptr<Object>& object, Scope scope) {
    bool constant = true;

    if(match(TokenType::Let)) {
        consume();
    } else if(match(TokenType::Const)) {
        constant = false;
        consume();
    }

    Identifier identifier = token().lexeme;
    consume(TokenType::Identifier,"identifier");
    consume(TokenType::Assign, "assignment operator '='");
    ptr<Value> value = expression() -> getValue();
    consume(TokenType::StatEnd, "';'");

    object -> getEnvironment() -> putAttribute(identifier, constant, value, scope);
}

void Parser::method(ptr<Object> &object, Scope scope) {
    consume();

    Identifier identifier = token().lexeme;
    consume(TokenType::Identifier, "identifier");

    consume(TokenType::LeftParen, "'('");
    IdentifierList parameters = identifierList();
    consume(TokenType::RightParen, "')'");

    ptr<Function> function = std::make_shared<Function>(parameters, *statementBlock());
    object -> getEnvironment() -> putFunction(identifier, function, scope);
}

IdentifierList Parser::identifierList() {
    IdentifierList identList;

    if(match(TokenType::RightParen))
        return identList;

    identList.push_back(token().lexeme);
    consume(TokenType::Identifier, "identifier");

    while(match(TokenType::Comma)) {
        consume();
        identList.push_back(token().lexeme);
        consume(TokenType::Identifier, "identifier");
    }

    return identList;
}

ExpressionList Parser::expressionList() {
     ExpressionList exprList;

     if(match(TokenType::RightParen))
         return exprList;

     exprList.push_back(expression());

     while(match(TokenType::Comma)) {
         consume();
         exprList.push_back(expression());
     }

     return exprList;
}

ptr<StatementBlock> Parser::statementBlock() {
    consume(TokenType::LeftCurly, "'{'");

    ptr<StatementBlock> statBlock = std::make_shared<StatementBlock>(statements());

    consume(TokenType::RightCurly, "'}'");

    return statBlock;
}

std::vector<ptr<Statement>> Parser::statements() {
    std::vector<ptr<Statement>> statList;
    while(!matchAny({ TokenType::RightCurly, TokenType::EndOfFile }))
        statList.push_back(statement());
}

ptr<Statement> Parser::statement() {
    ptr<Statement> stat;

    if(matchAny({ TokenType ::Let, TokenType::Const }))
        stat = localDecl(token().type);
    else if(match(TokenType::If))
        stat = ifStatement();
    else if(match(TokenType::While))
        stat = whileStatement();
    else if(match(TokenType::For))
        stat = forStatement();
    else if(match(TokenType::Try))
        stat = tryCatchStatement();
    else if(match(TokenType::Continue))
        stat = continueStatement();
    else if(match(TokenType::Break))
        stat = breakStatement();
    else if(match(TokenType::Throw))
        stat = throwStatement();
    else if(match(TokenType::Return))
        stat = returnStatement();
    else
        stat = expressionStatement();

    if(match(TokenType::Otherwise)) {
        stat = otherwiseStatement(stat);
    }

    return stat;
}

ptr<Statement> Parser::ifStatement() {
    consume();
    ptr<Expression> condition = expression();
    ptr<StatementBlock> ifBlock = statementBlock();
    ptr<StatementBlock> elseBlock;

    if(match(TokenType::Else)) {
        consume();
        elseBlock = statementBlock();
    }

    return std::make_shared<IfStatement>(condition, ifBlock, elseBlock);
}

ptr<Statement> Parser::whileStatement() {
    consume();
    ptr<Expression> condition = expression();

    functionCounter++;
    ptr<StatementBlock> statBlock = statementBlock();
    functionCounter--;

    return std::make_shared<WhileStatement>(condition, statBlock);
}

ptr<Statement> Parser::forStatement() {
    consume();
    Identifier identifier = token().lexeme;
    consume(TokenType::Identifier, "identifier");

    consume(TokenType::In, "'in'");

    ptr<Expression> iterable = expression();

    functionCounter++;
    ptr<StatementBlock> statBlock = statementBlock();
    functionCounter--;

    return std::make_shared<ForStatement>(identifier, iterable, statBlock);
}

ptr<Statement> Parser::tryCatchStatement() {
    consume();

    ptr<StatementBlock> tryBlock = statementBlock();
    consume(TokenType::Catch, "'catch'");

    Identifier identifier;
    if(match(TokenType::Identifier)) {
        identifier = token().lexeme;
        consume();
    }

    ptr<StatementBlock> catchBlock = statementBlock();

    return std::make_shared<TryCatchStatement>(identifier, tryBlock, catchBlock);
}

ptr<Statement> Parser::otherwiseStatement(ptr<Statement> stat) {
    consume();
    ptr<StatementBlock> statBlock = statementBlock();
    return std::make_shared<OtherwiseStatement>(std::move(stat), statBlock);
}

ptr<Statement> Parser::continueStatement() {
    if(functionCounter == 0)
        throw ParseException("Unexpected 'continue' outside a function.");

    consume();
    consume(TokenType::StatEnd, "';'");
    return std::make_shared<ContinueStatement>();
}

ptr<Statement> Parser::breakStatement() {
    if(functionCounter == 0)
        throw ParseException("Unexpected 'continue' outside a function.");

    consume();
    consume(TokenType::StatEnd, "';'");
    return std::make_shared<BreakStatement>();
}

ptr<Statement> Parser::returnStatement() {
    consume();
    ptr<Expression> toReturn;

    if(!match(TokenType::StatEnd)) {
        toReturn = expression();
    }
    consume(TokenType::StatEnd, "';'");
    return std::make_shared<ReturnStatement>(toReturn);
}

ptr<Statement> Parser::throwStatement() {
    consume();
    ptr<Expression> toThrow;

    if(!match(TokenType::StatEnd)) {
        toThrow = expression();
    }
    consume(TokenType::StatEnd, "';'");
    return std::make_shared<ThrowStatement>(toThrow);
}

ptr<Statement> Parser::localDecl(TokenType tokenType) {
    log("local variable declaration");
    consume();
    consume(TokenType::Identifier, "identifier");
    consume(TokenType::Assign, "assignment operator '='");
    expression();
    consume(TokenType::StatEnd, "';'");
}

ptr<Statement> Parser::expressionStatement() {
    ptr<Expression> expr = expression();
    consume(TokenType::StatEnd, "';'");
    return std::make_shared<ExpressionStatement>(expr);
}

ptr<Expression> Parser::expression() {
    log("expression");
    logOr();
    if(matchAny({ TokenType::Assign, TokenType::PlusAssign, TokenType::MultAssign, TokenType::MinusAssign, TokenType::DivAssign, TokenType::ExpAssign, TokenType::ModAssign })) {
        consume();
        logOr();
    }
    return std::make_shared<String>("EXPRESSION");
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
    merge();
    while(matchAny({ TokenType::Mult, TokenType::Div, TokenType::Mod, TokenType::Exp })) {
        consume();
        merge();
    }
}

void Parser::merge() {
    log("factor");
    unary();
    while(match(TokenType::Merge)) {
        consume();
        unary();
    }
}

void Parser::unary() {
    log("unary");
    while(matchAny({ TokenType::Neg, TokenType::Minus }))
        consume();

    if(match(TokenType::New)) {
        log("There is a new one!");
        consume();
    }

    primary();

    if(match(TokenType::As)) {
        consume();
        if(!matchAny({ TokenType::StringType, TokenType::IntegerType, TokenType::DoubleType, TokenType::BooleanType })) {
            log("Cast");
            unexpected();
        } else {
            consume();
        }
    }
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
