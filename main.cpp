#include <iostream>
#include <sstream>

#include "include/Parser.h"
#include "include/Interpreter.h"
#include "include/ParseException.h"
#include "include/AbstractSyntaxTree/ValueExpression/ObjectExpression.h"
#include "include/AbstractSyntaxTree/Packets.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Usage: katon <filepath>" << std::endl;
        return 0;
    }

    char* filename = argv[1];

    try {
        Parser parser(filename);
        ptr<ObjectExpression> moduleDescriptor = parser.parse();
        ptr<Object> module = moduleDescriptor -> evaluate(nullptr) -> asObject();

        Interpreter interpreter(module);
        interpreter.execute();

    } catch(ParseException& e) {
        std::cout << e.what() << std::endl;
    } catch(ThrowPacket& packet) {
        std::cout << "Error: " << packet.getValue() -> asString() << std::endl;
    }

    return 0;
}
