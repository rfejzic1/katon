#include "../include/Interpreter.h"

#include "../include/AbstractSyntaxTree/FunctionSymbol.h"

void Interpreter::execute() {
    ptr<Symbol> mainSymbol = object -> getEnvironment() -> getMember("main");
    if (!mainSymbol)
        throw RuntimeException("'main' is not defined.");

    ptr<FunctionSymbol> mainFunctionSymbol = std::dynamic_pointer_cast<FunctionSymbol>(mainSymbol);

    if (!mainFunctionSymbol)
        throw RuntimeException("Member 'main' is not a function.");

    ptr<Function> main = mainFunctionSymbol -> getFunction();
    ValueList initial = {};
    main -> call(object.get(), initial);
}