#include <iostream>

#include "include/Parser.h"
#include "include/Interpreter.h"
#include "include/ParseException.h"
#include "include/RuntimeException.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Usage: katon <filepath>" << std::endl;
        return 0;
    }

    char* filename = argv[1];

    try {
        Parser parser(filename);
        Object* object = parser.parse();

        Interpreter interpreter(object);
        interpreter.execute();

    } catch(ParseException& e) {
        std::cout << e.what() << std::endl;
    } catch(RuntimeException& e) {
        std::cout << e.what() << std::endl;
    } catch(...) {
        std::cout << "Could not load file..." << std::endl;
    }

    return 0;
}
