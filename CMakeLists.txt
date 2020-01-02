cmake_minimum_required(VERSION 3.15)
project(Katon)

set(CMAKE_CXX_STANDARD 17)

add_executable(Katon main.cpp src/Klex.cpp include/Klex.h include/Token.h src/Parser.cpp include/Parser.h src/AbstractSyntaxTree.cpp include/AbstractSyntaxTree/AbstractSyntaxTree.h include/ParseException.h include/AbstractSyntaxTree/Node.h src/Interpreter.cpp include/Interpreter.h include/AbstractSyntaxTree/Operators/BinaryOperator.h include/AbstractSyntaxTree/Nodes.h include/AbstractSyntaxTree/Symbol.h include/AbstractSyntaxTree/AttributeDeclaration.h include/AbstractSyntaxTree/Values/Value.h include/AbstractSyntaxTree/Expression.h include/AbstractSyntaxTree/Values/Primitives/Integer.h include/AbstractSyntaxTree/Values/Primitives/Double.h include/AbstractSyntaxTree/Values/Primitives/Boolean.h include/AbstractSyntaxTree/Values/Primitives/String.h include/AbstractSyntaxTree/Values/Primitives/Primitive.h)