#include <iostream>
#include <sstream>

#include "../include/Parser.h"
#include "../include/AbstractSyntaxTree/Function.h"
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
#include "../include/AbstractSyntaxTree/Statements/LocalDeclarationStatement.h"
#include "../include/AbstractSyntaxTree/ValueExpression/ObjectExpression.h"
#include "../include/AbstractSyntaxTree/ValueExpression/PrimitiveExpression.h"
#include "../include/AbstractSyntaxTree/ValueExpression/ArrayExpression.h"
#include "../include/AbstractSyntaxTree/Operators/Assignment.h"
#include "../include/AbstractSyntaxTree/Operators/Addition.h"
#include "../include/AbstractSyntaxTree/Operators/Multiplication.h"
#include "../include/AbstractSyntaxTree/Operators/Subtraction.h"
#include "../include/AbstractSyntaxTree/Operators/Division.h"
#include "../include/AbstractSyntaxTree/Operators/Exponentiation.h"
#include "../include/AbstractSyntaxTree/Operators/Modulo.h"
#include "../include/AbstractSyntaxTree/Operators/Disjunction.h"
#include "../include/AbstractSyntaxTree/Operators/Conjunction.h"
#include "../include/AbstractSyntaxTree/Operators/Equality.h"
#include "../include/AbstractSyntaxTree/Operators/Inequality.h"
#include "../include/AbstractSyntaxTree/Operators/LessThan.h"
#include "../include/AbstractSyntaxTree/Operators/LessThanOrEqual.h"
#include "../include/AbstractSyntaxTree/Operators/GreaterThan.h"
#include "../include/AbstractSyntaxTree/Operators/GreaterThanOrEqual.h"
#include "../include/AbstractSyntaxTree/Operators/Merge.h"
#include "../include/AbstractSyntaxTree/Operators/New.h"
#include "../include/AbstractSyntaxTree/Operators/Negation.h"
#include "../include/AbstractSyntaxTree/Operators/Negative.h"
#include "../include/AbstractSyntaxTree/Operators/Cast.h"
#include "../include/AbstractSyntaxTree/Operators/MemberAccess.h"
#include "../include/AbstractSyntaxTree/Operators/Call.h"
#include "../include/AbstractSyntaxTree/Operators/ElementAccess.h"

Parser::Parser(const char *filepath) : filepath(filepath), klex(nullptr) { }

ptr<ObjectExpression> Parser::parse() {
    openKlex();

    consume();
    ptr<ObjectExpression> moduleDescriptor = module();

    return moduleDescriptor;
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
    msg << "Parse error on line " << token().line <<  " column " << token().col << ":\n\t" << message;
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

ptr<ObjectExpression> Parser::module() {
    ptr<ObjectExpression> objectDescriptor = make<ObjectExpression>();
    while(!match(TokenType::EndOfFile)) {
        memberDecl(objectDescriptor);
    }
    return objectDescriptor;
}

ptr<ObjectExpression> Parser::object() {
    ptr<ObjectExpression> objectDescriptor = make<ObjectExpression>();

    consume(TokenType::LeftCurly, "'{'");
    while(!match(TokenType::RightCurly) && !match(TokenType::EndOfFile)) {
        memberDecl(objectDescriptor);
    }
    consume(TokenType::RightCurly, "'}'");

    return objectDescriptor;
}

ptr<ArrayExpression> Parser::array() {
    consume(TokenType::LeftBrack, "'['");
    ptr<ArrayExpression> expr = make<ArrayExpression>(expressionList());
    consume(TokenType::RightBrack, "']'");
    return expr;
}

void Parser::memberDecl(ptr<ObjectExpression> &descriptor) {
    Scope scope = Scope::Public;

    if(match(TokenType::Public)) {
        consume();
    } else if(match(TokenType::Private)) {
        scope = Scope::Private;
        consume();
    }

    if(matchAny({ TokenType::Let, TokenType::Const, TokenType::Identifier }))
        attributeDecl(descriptor, scope);
    else if(match(TokenType::Function))
        method(descriptor, scope);
    else {
        unexpected();
    }
}

void Parser::attributeDecl(ptr<ObjectExpression> &descriptor, Scope scope) {
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
    ptr<Expression> expr = expression();
    consume(TokenType::StatEnd, "';'");

     descriptor -> putExpression(identifier, scope, expr, constant);
}

void Parser::method(ptr<ObjectExpression> &descriptor, Scope scope) {
    consume();

    Identifier identifier = token().lexeme;
    consume(TokenType::Identifier, "identifier");

    consume(TokenType::LeftParen, "'('");
    IdentifierList parameters = identifierList();
    consume(TokenType::RightParen, "')'");

    ptr<Function> function = make<Function>(make<IdentifierList>(parameters), statementBlock());
    descriptor -> putFunction(identifier, scope, function);
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

    ptr<StatementBlock> statBlock = make<StatementBlock>(statements());

    consume(TokenType::RightCurly, "'}'");

    return statBlock;
}

std::vector<ptr<Statement>> Parser::statements() {
    std::vector<ptr<Statement>> statList;
    while(!matchAny({ TokenType::RightCurly, TokenType::EndOfFile }))
        statList.push_back(statement());
    return statList;
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

    return make<IfStatement>(condition, ifBlock, elseBlock);
}

ptr<Statement> Parser::whileStatement() {
    consume();
    ptr<Expression> condition = expression();

    functionCounter++;
    ptr<StatementBlock> statBlock = statementBlock();
    functionCounter--;

    return make<WhileStatement>(condition, statBlock);
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

    return make<ForStatement>(identifier, iterable, statBlock);
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

    return make<TryCatchStatement>(identifier, tryBlock, catchBlock);
}

ptr<Statement> Parser::otherwiseStatement(ptr<Statement> stat) {
    consume();
    ptr<StatementBlock> statBlock = statementBlock();
    return make<OtherwiseStatement>(std::move(stat), statBlock);
}

ptr<Statement> Parser::continueStatement() {
    if(functionCounter == 0)
        error("Unexpected 'continue' outside a function.");

    consume();
    consume(TokenType::StatEnd, "';'");
    return make<ContinueStatement>();
}

ptr<Statement> Parser::breakStatement() {
    if(functionCounter == 0)
        error("Unexpected 'continue' outside a function.");

    consume();
    consume(TokenType::StatEnd, "';'");
    return make<BreakStatement>();
}

ptr<Statement> Parser::returnStatement() {
    consume();
    ptr<Expression> toReturn;

    if(!match(TokenType::StatEnd)) {
        toReturn = expression();
    }
    consume(TokenType::StatEnd, "';'");
    return make<ReturnStatement>(toReturn);
}

ptr<Statement> Parser::throwStatement() {
    consume();
    ptr<Expression> toThrow;

    if(!match(TokenType::StatEnd)) {
        toThrow = expression();
    }
    consume(TokenType::StatEnd, "';'");
    return make<ThrowStatement>(toThrow);
}

ptr<Statement> Parser::localDecl(TokenType tokenType) {
    bool constant = tokenType == TokenType::Const;
    consume();
    Identifier identifier = token().lexeme;
    consume(TokenType::Identifier, "identifier");
    consume(TokenType::Assign, "assignment operator '='");
    ptr<Expression> expr = expression();
    consume(TokenType::StatEnd, "';'");
    return make<LocalDeclarationStatement>(identifier, constant, expr);
}

ptr<Statement> Parser::expressionStatement() {
    ptr<Expression> expr = expression();
    consume(TokenType::StatEnd, "';'");
    return make<ExpressionStatement>(expr);
}

ptr<Expression> Parser::expression() {
    ptr<Expression> expr = disjunction();

    if(matchAny({ TokenType::Assign, TokenType::PlusAssign, TokenType::MultAssign, TokenType::MinusAssign, TokenType::DivAssign, TokenType::ExpAssign, TokenType::ModAssign })) {
        // todo: Do a better symbol check!!!
        ptr<Symbol> symbol = std::dynamic_pointer_cast<Symbol>(expr);
        if(!symbol)
            error("The left operand of the assignment operator is not an lvalue");

        TokenType assignType = token().type;
        consume();
        ptr<Operation> additionalOperation;

        if(assignType == TokenType::PlusAssign)
            additionalOperation = make<Addition>();
        else if(assignType == TokenType::MultAssign)
            additionalOperation = make<Multiplication>();
        else if(assignType == TokenType::MinusAssign)
            additionalOperation = make<Subtraction>();
        else if(assignType == TokenType::DivAssign)
            additionalOperation = make<Division>();
        else if(assignType == TokenType::ExpAssign)
            additionalOperation = make<Exponentiation>();
        else if(assignType == TokenType::ModAssign)
            additionalOperation = make<Modulo>();

        expr = make<Assignment>(additionalOperation, symbol, disjunction());
    }

    return expr;
}

ptr<Expression> Parser::disjunction() {
    ptr<Expression> expr = conjunction();

    if(match(TokenType::Or)) {
        consume();
        expr = make<BinaryOperator>(make<Disjunction>(), expr, disjunction());
    }

    return expr;
}

ptr<Expression> Parser::conjunction() {
    ptr<Expression> expr = equality();

    if(match(TokenType::And)) {
        consume();
        expr = make<BinaryOperator>(make<Conjunction>(), expr, conjunction());
    }

    return expr;
}

ptr<Expression> Parser::equality() {
    ptr<Expression> expr = comparison();

    if(match(TokenType::Equals)) {
        consume();
        expr = make<BinaryOperator>(make<Equality>(), expr, equality());
    }else if(match(TokenType::NotEqu)) {
        consume();
        expr = make<BinaryOperator>(make<Inequality>(), expr, equality());
    }

    return expr;
}

ptr<Expression> Parser::comparison() {
    ptr<Expression> expr = term();

    if(match(TokenType::LThan)) {
        consume();
        expr = make<BinaryOperator>(make<LessThan>(), expr, comparison());
    } else if(match(TokenType::LThanEqu)) {
        consume();
        expr = make<BinaryOperator>(make<LessThanOrEqual>(), expr, comparison());
    } else if(match(TokenType::GThanEqu)) {
        consume();
        expr = make<BinaryOperator>(make<GreaterThan>(), expr, comparison());
    } else if(match(TokenType::GThanEqu)) {
        consume();
        expr = make<BinaryOperator>(make<GreaterThanOrEqual>(), expr, comparison());
    }

    return expr;
}

ptr<Expression> Parser::term() {
    ptr<Expression> expr = factor();

    if(match(TokenType::Plus)) {
        consume();
        expr = make<BinaryOperator>(make<Addition>(), expr, term());
    } else if(match(TokenType::Minus)) {
        consume();
        expr = make<BinaryOperator>(make<Subtraction>(), expr, term());
    }

    return expr;
}

ptr<Expression> Parser::factor() {
    ptr<Expression> expr = merge();

    if(match(TokenType::Mult)) {
        consume();
        expr = make<BinaryOperator>(make<Multiplication>(), expr, factor());
    } else if(match(TokenType::Div)) {
        consume();
        expr = make<BinaryOperator>(make<Division>(), expr, factor());
    } else if(match(TokenType::Exp)) {
        consume();
        expr = make<BinaryOperator>(make<Exponentiation>(), expr, factor());
    } else if(match(TokenType::Mod)) {
        consume();
        expr = make<BinaryOperator>(make<Modulo>(), expr, factor());
    }

    return expr;
}

ptr<Expression> Parser::merge() {
    ptr<Expression> expr = castable();

    if(match(TokenType::Merge)) {
        consume();
        expr = make<BinaryOperator>(make<Merge>(), expr, merge());
    }

    return expr;
}

ptr<Expression> Parser::castable() {
    ptr<Expression> expr = unary();

    if(match(TokenType::As)) {
        consume();

        if(match(TokenType::StringType)) {
            consume();
            expr = make<Cast>(expr, Type::String);
        } else if(match(TokenType::DoubleType)) {
            consume();
            expr = make<Cast>(expr, Type::Double);
        } else if(match(TokenType::IntegerType)) {
            consume();
            expr = make<Cast>(expr, Type::Integer);
        } else if(match(TokenType::BooleanType)) {
            consume();
            expr = make<Cast>(expr, Type::Boolean);
        } else {
            unexpected();
        }
    }

    return expr;
}

ptr<Expression> Parser::unary() {
    if(match(TokenType::Neg)) {
        consume();
        return make<Negation>(unary());
    }

    if(match(TokenType::Minus)) {
        consume();
        return make<Negative>(unary());
    }

    bool isNew = false;
    if(match(TokenType::New)) {
        consume();
        isNew = true;
    }

    ptr<Expression> expr = primary();

    if(isNew) {
        expr = make<New>(expr);
    }

    return expr;
}

ptr<Expression> Parser::primary() {
    if(match(TokenType::Identifier)) {
        ptr<Expression> expr = variable();
        return postfix(expr);
    } else if(match(TokenType::LeftParen)) {
        consume(TokenType::LeftParen, "'('");
        ptr<Expression> expr = expression();
        consume(TokenType::RightParen, "')'");
        return expr;
    } else {
        return value();
    }
}

ptr<Expression> Parser::value() {
    if(matchAny({ TokenType::True, TokenType::False })) {
        bool logicalValue = token().type == TokenType::True;
        consume();
        return make<PrimitiveExpression<Boolean>>(logicalValue);

    } else if(match(TokenType::Number)) {
        long long int integerValue = std::stoll(token().lexeme);
        double doubleValue = std::stod(token().lexeme);
        consume();

        if(integerValue == doubleValue) {
            return make<PrimitiveExpression<Integer>>(integerValue);
        }

        return make<PrimitiveExpression<Double>>(doubleValue);

    } else if(match(TokenType::SingleQuote)) {
        consume();
        ptr<Expression> expr = make<PrimitiveExpression<String>>(token().lexeme);
        consume(TokenType::String, "string");
        consume(TokenType::SingleQuote, "\"'\"");
        return expr;

    } else if(match(TokenType::DoubleQuote)) {
        consume();
        ptr<Expression> expr = make<PrimitiveExpression<String>>(token().lexeme);
        consume(TokenType::String, "string");
        consume(TokenType::DoubleQuote, "'\"'");
        return expr;

    } else if(match(TokenType::LeftCurly)) {
        return object();
    } else if(match(TokenType::LeftBrack)) {
        return array();
    } else if(match(TokenType::Lambda)) {
        return lambda();
    } else {
        unexpected();
    }
}

ptr<Expression> Parser::lambda() {
    consume();
    consume(TokenType::LeftParen, "'('");
    IdentifierList parameters = identifierList();
    consume(TokenType::RightParen, "')'");

    ptr<Function> function = make<Function>(make<IdentifierList>(parameters), statementBlock());

    ptr<ObjectExpression> objectDescriptor = make<ObjectExpression>();
    objectDescriptor -> putFunction("call", Scope::Public, function);
    return objectDescriptor;
}

ptr<Expression> Parser::variable() {
    Identifier ident = token().lexeme;
    consume(TokenType::Identifier, "identifier");
    ptr<Expression> expr = make<Symbol>(ident);
    return expr;
}

ptr<Expression> Parser::postfix(ptr<Expression> callee) {
    if(match(TokenType::LeftParen)) {
        return call(callee);
    } else if(match(TokenType::LeftBrack)) {
        return access(callee);
    } else if(match(TokenType::Dot)) {
        return memberAccess(callee);
    }
    return callee;
}

ptr<Expression> Parser::call(ptr<Expression> callee) {
    consume();
    ExpressionList exprList = expressionList();
    consume(TokenType::RightParen, "')'");

    ptr<Expression> expr = make<Call>(callee, exprList);
    return postfix(expr);
}

ptr<Expression> Parser::access(ptr<Expression> callee) {
    consume();
    ptr<Expression> accessValue = expression();
    consume(TokenType::RightBrack, "']'");
    ptr<Expression> expr = make<ElementAccess>(callee, accessValue);
    return postfix(expr);
}

ptr<Expression> Parser::memberAccess(ptr<Expression> callee) {
    consume();
    ptr<Expression> expr = make<MemberAccess>(callee, variable());
    return postfix(expr);
}
