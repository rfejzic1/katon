#pragma once

#include <fstream>
#include <string>
#include <unordered_map>

#include "Token.h"

enum class CharClass {
    DIGIT, LETTER, SINGLE_QUOTE, DOUBLE_QUOTE, OTHER
};

class Klex {
    FILE* file;
    std::unordered_map<std::string, TokenType> lexToTokenTable;

    char currentChar = 0;
    CharClass charClass = CharClass::OTHER;

    TokenType tokenType = TokenType::Unknown;
    std::string lexeme;
    long lineNum = 1;


    bool isSimpleString = false;
    bool isInterpolatedString = false;
    bool shouldparseOutString = false;

    char getChar();
    CharClass getCharClass();
    bool nextChar();
    void skipWhitespace();
    void skipComment();

    TokenType getTokenTypeOfLexeme(std::string &lexeme, bool isWord = false);
    std::string parseOutWord();
    std::string parseOutNumber();
    std::string parseOutSymbol();
    std::string parseOutString(char quote);

    void initLexToTokenTable();
public:
    Klex(const char* filepath);
    bool nextToken();
    Token getToken();
    ~Klex();
};