#include "../include/Interpreter.h"

#include "../include/AbstractSyntaxTree/Function.h"

void Interpreter::execute() {
    ptr<Function> main = object -> getFunction("main");

    if(!main)
        throw ThrowPacket(ExceptionObjects::undefined("No function named 'main' is defined"));

    ValueList initial = {};
    main -> call(object, initial);
}
