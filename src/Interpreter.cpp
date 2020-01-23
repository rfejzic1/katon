#include "../include/Interpreter.h"

#include "../include/AbstractSyntaxTree/FunctionSymbol.h"

void Interpreter::execute() {
    ptr<FunctionSymbol> mainSymbol = object -> getEnvironment() -> getFunction("main");

    if(!mainSymbol)
        throw ThrowPacket(ExceptionObjects::undefined("No function named 'main' is defined"));

    ptr<Function> main = mainSymbol -> getFunction();
    ValueList initial = {};
    main -> call(object, initial);
}
