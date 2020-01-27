#include <iostream>
#include <sstream>

#include "include/Parser.h"
#include "include/Interpreter.h"
#include "include/ParseException.h"
#include "include/RuntimeException.h"
#include "include/AbstractSyntaxTree/Symbol.h"
#include "include/AbstractSyntaxTree/ObjectDescriptor.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Usage: katon <filepath>" << std::endl;
        return 0;
    }

    char* filename = argv[1];

    try {
        Parser parser(filename);
        ptr<ObjectDescriptor> moduleDescriptor = parser.parse();
        ptr<Object> module = moduleDescriptor -> evaluate(nullptr) -> asObject();

        std::cout << "Parse complete" << std::endl;

        Interpreter interpreter(module);
        interpreter.execute();

    } catch(ParseException& e) {
        std::cout << e.what() << std::endl;
    } catch(ThrowPacket& packet) {
        std::stringstream str;
        ptr<Object> exception = packet.getValue() -> asObject();
        auto type = exception->getAttribute("type")->evaluate(exception->getEnvironment()) -> asString();
        auto message = exception->getAttribute("message")->evaluate(exception->getEnvironment()) -> asString();

        str << "Unhandled exception of type '" << type << "':" << std::endl
        << "\t" << message << std::endl;
        std::cout << str.str() << std::endl;
    }

    return 0;
}
