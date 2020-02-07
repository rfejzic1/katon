#include "../include/Interpreter.h"

#include <chrono>

#include "../include/AbstractSyntaxTree/Function.h"

void Interpreter::execute(bool showExecutionTime) {
    ptr<Function> main = object -> getFunction("main");

    if(!main)
        throw ThrowPacket(ExceptionObjects::undefined("No function named 'main' is defined"));

    auto start = std::chrono::high_resolution_clock::now();

    try {
        ValueList initial = {};
        main -> call(initial);
    } catch(ReturnPacket& returnPacket) {}

    if(showExecutionTime) {
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << std::endl << "Executed in " << duration.count() << " ms" << std::endl;
    }
}
