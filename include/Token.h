#pragma once

enum class TokenType {
    // quotes
    SingleQuote,
    DoubleQuote,
    // brackts
    LeftParen,
    RightParen,
    LeftBrack,
    RightBrack,
    LeftCurly,
    RightCurly,
    // comparison
    Equals,
    NotEqu,
    LThan,
    GThan,
    LThanEqu,
    GThanEqu,
    // logical
    Neg,
    And,
    Or,
    // assignemnt
    Assign,
    PlusAssign,
    MinusAssign,
    MultAssign,
    DivAssign,
    ModAssign,
    ExpAssign,
    // operators
    Plus,
    Minus,
    Mult,
    Div,
    Mod,
    Exp,
    Dot,
    Merge,
    Arrow,
    Use,
    New,
    // controll
    If,
    ElseIf,
    Else,
    While,
    For,
    In,
    Try,
    Catch,
    // other
    Let,
    Const,
    Private,
    Public,
    Comma,
    StatEnd,
    Identifier,
    String,
    Number,
    Otherwise,
    Unknown,
    StringType,
    IntegerType,
    DoubleType,
    BooleanType
};

struct Token {
    TokenType type = TokenType::Unknown;
    std::string lexeme;
    long line = -1;

    Token() {}

    Token(std::string lexeme, TokenType type, long line) {
        Token::type = type;
        Token::lexeme = lexeme;
        Token::line = line;
    }
};
