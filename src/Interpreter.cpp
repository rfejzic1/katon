#include "../include/Interpreter.h"

#include "../include/AbstractSyntaxTree/Function.h"
#include "../include/AbstractSyntaxTree/ExceptionObjects.h"
#include "../include/AbstractSyntaxTree/Packets.h"

void Interpreter::execute() {
    ptr<Function> main = object -> getFunction("main");

    if(!main)
        throw ThrowPacket(ExceptionObjects::undefined("No function named 'main' is defined"));

    ValueList initial = {};
    try {
        main -> call(initial);
    } catch(ReturnPacket& returnPacket) {

    }
}
