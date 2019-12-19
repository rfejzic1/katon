#include "../include/Klex.h"
#include <cctype>

Klex::Klex(const char* filepath) {
    file = fopen(filepath, "r");
    if(!file)
        throw "Could not open file!";
    initLexToTokenTable();

    nextChar();
}

void Klex::initLexToTokenTable() {
    lexToTokenTable["("] = TokenType::LeftParen;
    lexToTokenTable[")"] = TokenType::RightParen;
    lexToTokenTable["["] = TokenType::LeftBrack;
    lexToTokenTable["]"] = TokenType::RightBrack;
    lexToTokenTable["{"] = TokenType::LeftCurly;
    lexToTokenTable["}"] = TokenType::RightCurly;
    lexToTokenTable["=="] = TokenType::Equals;
    lexToTokenTable["!="] = TokenType::NotEqu;
    lexToTokenTable["<"] = TokenType::LThan;
    lexToTokenTable[">"] = TokenType::GThan;
    lexToTokenTable["<="] = TokenType::LThanEqu;
    lexToTokenTable[">="] = TokenType::GThanEqu;
    lexToTokenTable["not"] = TokenType::Neg;
    lexToTokenTable["and"] = TokenType::And;
    lexToTokenTable["or"] = TokenType::Or;
    lexToTokenTable["="] = TokenType::Assign;
    lexToTokenTable["+="] = TokenType::PlusAssign;
    lexToTokenTable["-="] = TokenType::MinusAssign;
    lexToTokenTable["*="] = TokenType::MultAssign;
    lexToTokenTable["/="] = TokenType::DivAssign;
    lexToTokenTable["%="] = TokenType::ModAssign;
    lexToTokenTable["^="] = TokenType::ExpAssign;
    lexToTokenTable["+"] = TokenType::Plus;
    lexToTokenTable["-"] = TokenType::Minus;
    lexToTokenTable["*"] = TokenType::Mult;
    lexToTokenTable["/"] = TokenType::Div;
    lexToTokenTable["%"] = TokenType::Mod;
    lexToTokenTable["^"] = TokenType::Exp;
    lexToTokenTable["."] = TokenType::Dot;
    lexToTokenTable["=>"] = TokenType::Arrow;
    lexToTokenTable["use"] = TokenType::Use;
    lexToTokenTable["new"] = TokenType::New;
    lexToTokenTable["if"] = TokenType::If;
    lexToTokenTable["elseif"] = TokenType::ElseIf;
    lexToTokenTable["else"] = TokenType::Else;
    lexToTokenTable["while"] = TokenType::While;
    lexToTokenTable["for"] = TokenType::For;
    lexToTokenTable["in"] = TokenType::In;
    lexToTokenTable["try"] = TokenType::Try;
    lexToTokenTable["catch"] = TokenType::Catch;
    lexToTokenTable["var"] = TokenType::Let;
    lexToTokenTable["const"] = TokenType::Const;
    lexToTokenTable["public"] = TokenType::Private;
    lexToTokenTable["private"] = TokenType::Public;
    lexToTokenTable["otherwise"] = TokenType::Otherwise;
    lexToTokenTable[","] = TokenType::Comma;
    lexToTokenTable[";"] = TokenType::StatEnd;
    lexToTokenTable["String"] = TokenType::StringType;
    lexToTokenTable["Number"] = TokenType::NumberType;
    lexToTokenTable["Boolean"] = TokenType::BooleanType;
}

char Klex::getChar() {
    return chara;
}

CharClass Klex::getCharClass() {
    return charClass;
}

void Klex::skipComment() {
    if(chara == '#') {
        while(chara != '\n' && chara != '\r' && chara != EOF) {
            chara = fgetc(file);
        }
    }
}

bool Klex::nextChar() {
    chara = fgetc(file);

    skipComment();

    if(isalpha(chara) || chara == '_') {
        charClass = CharClass::LETTER;
    } else if(isdigit(chara)) {
        charClass = CharClass::DIGIT;
    } else if(chara == '\'') {
        charClass = CharClass::SINGLE_QUOTE;
    } else if(chara == '"') {
        charClass = CharClass::DOUBLE_QUOTE;
    } else {
        charClass = CharClass::OTHER;
    }

    return chara != EOF;
}

void Klex::skipWhitespace() {
    char c = getChar();

    while(c == ' ' || c == '\t' || c == '\n' || c == '\r') {
        if(c == '\n')
            lineNum++;

        nextChar();
        c = getChar();
    }
}

// refactor this!!!
bool Klex::nextToken() {
    if(getChar() == EOF)
        return false;

    if(!isInterpolatedString && !isSimpleString)
        skipWhitespace();

    if(shouldparseOutString && isSimpleString) {
        lexeme = parseOutString('\'');
        tokenType = TokenType::String;
        shouldparseOutString = false;
        return true;
    }

    if(shouldparseOutString && isInterpolatedString) {
        lexeme = parseOutString('"');
        tokenType = TokenType::String;
        shouldparseOutString = false;
        return true;
    }

    switch(getCharClass()) {
        case CharClass::LETTER:
            lexeme = parseOutWord();
            tokenType = getTokenTypeOfLexeme(lexeme, true);
            break;
        case CharClass::DIGIT:
            lexeme = parseOutNumber();
            tokenType = TokenType::Number;
            break;
        case CharClass::SINGLE_QUOTE:
            if(!isSimpleString)
                shouldparseOutString = true;
            isSimpleString = !isSimpleString;
            lexeme = parseOutSymbol();
            tokenType = TokenType::SingleQuote;
            break;
        case CharClass::DOUBLE_QUOTE:
            if(!isInterpolatedString)
                shouldparseOutString = true;
            isInterpolatedString = !isInterpolatedString;
            lexeme = parseOutSymbol();
            tokenType = TokenType::DoubleQuote;
            break;
        case CharClass::OTHER:
            lexeme = parseOutSymbol();
            tokenType = getTokenTypeOfLexeme(lexeme);
            break;
    }

    return true;
}

std::string Klex::parseOutWord() {
    std::string lexeme;

    while(getCharClass() == CharClass::LETTER || getCharClass() == CharClass::DIGIT) {
        lexeme.push_back(getChar());
        nextChar();
    }

    return lexeme;
}

std::string Klex::parseOutNumber() {
    std::string lexeme;
    bool onePoint = false;

    while(getCharClass() == CharClass::DIGIT) {
        lexeme += getChar();
        nextChar();

        if(getChar() == '.') {
            if(onePoint)
                break;

            onePoint = true;
            lexeme.push_back(getChar());
            nextChar();
        }
    }

    return lexeme;
}

std::string Klex::parseOutSymbol() {
    std::string lexeme;

    // Double char symbols
    // == =>
    // != >= <= += -= *= /= %= ^=

    std::string equFirstSymbols = "=>";
    std::string equSecondSymbols = "!><+-*/%^";

    lexeme.push_back(getChar());

    if(getChar() == '=') {
        nextChar();
        if(equFirstSymbols.find(getChar()) != -1) {
            lexeme.push_back(getChar());
            nextChar();
        }
    } else if(equSecondSymbols.find(getChar()) != -1) {
        nextChar();
        if(getChar() == '=') {
            lexeme.push_back(getChar());
            nextChar();
        }
    }else {
        nextChar();
    }

    return lexeme;
}

std::string Klex::parseOutString(char quote) {
    std::string lexeme;

    while(getChar() != EOF && getChar() != quote) {
        lexeme.push_back(getChar());
        nextChar();
    }

    return lexeme;
}

TokenType Klex::getTokenTypeOfLexeme(std::string &lexeme, bool isWord) {
    if (lexToTokenTable.find(lexeme) == lexToTokenTable.end())
        return isWord ? TokenType::Identifier : TokenType::Unknown;

    return lexToTokenTable[lexeme];
}

Token Klex::getToken() {
    return Token(lexeme, tokenType, lineNum);
}

Klex::~Klex() {
    fclose(file);
}
