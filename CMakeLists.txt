cmake_minimum_required(VERSION 3.15)
project(Katon)

set(CMAKE_CXX_STANDARD 17)

add_executable(Katon main.cpp src/Klex.cpp include/Klex.h include/Token.h src/Parser.cpp include/Parser.h src/AbstractSyntaxTree.cpp include/AbstractSyntaxTree.h include/ParseException.h include/Nodes/Node.h src/Interpreter.cpp include/Interpreter.h include/Nodes/BinaryNode.h include/Nodes/Nodes.h include/Nodes/NaryNode.h)