#pragma once

enum class TokenType {
    SingleQuote = 0,
    DoubleQuote,
    LeftParen,
    RightParen,
    LeftBrack,
    RightBrack,
    LeftCurly,
    RightCurly,
    Equals,
    NotEqu,
    LThan,
    GThan,
    LThanEqu,
    GThanEqu,
    Neg,
    And,
    Or,
    Assign,
    PlusAssign,
    MinusAssign,
    MultAssign,
    DivAssign,
    ModAssign,
    ExpAssign,
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
    BooleanType,
    Function,
    True,
    False
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
