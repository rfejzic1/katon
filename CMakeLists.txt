cmake_minimum_required(VERSION 3.15)
project(Katon)

set(CMAKE_CXX_STANDARD 17)

add_executable(Katon main.cpp Klex/Klex.cpp Klex/Klex.h Klex/Token.h Parser/Parser.cpp Parser/Parser.h AbstractSyntaxTree/AbstractSyntaxTree.cpp AbstractSyntaxTree/AbstractSyntaxTree.h Common/ParseException.h AbstractSyntaxTree/Nodes/Node.h Interpreter/Interpreter.cpp Interpreter/Interpreter.h AbstractSyntaxTree/Nodes/BinaryNode.h AbstractSyntaxTree/Nodes/Nodes.h AbstractSyntaxTree/Nodes/NaryNode.h)