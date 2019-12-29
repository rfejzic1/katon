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
    False,
    Return,
    Break,
    Continue,
    Throw,
    Lambda,
    EndOfFile
};

struct Token {
    TokenType type = TokenType::Unknown;
    std::string lexeme;
    long line = -1;
    long col = -1;

    Token() {}

    Token(std::string lexeme, TokenType type, long line, long col) {
        Token::type = type;
        Token::lexeme = lexeme;
        Token::line = line;
        Token::col = col;
    }
};
