#pragma once

// ToDo Abstract Syntax Tree
//  - Literal nodes
//  - Expression nodes
//  - Statement nodes
//  - Nodes for control statements and code blocks
//  - Should the tree be a binary tree???
//  - Operator precedence, left and right association
//  - Symbol table

#include <string>
#include <vector>

#include "../AbstractSyntaxTree/AbstractSyntaxTree.h"
#include "../Klex/Klex.h"

class Parser {
    std::string filepath;
    std::vector<Token> tokens;

    void readTokenStream();

    void error(const char* message);
    void log(const char* message);

public:
    Parser(const char* filepath);
    AbstractSyntaxTree parse();
};

