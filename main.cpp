#include <iostream>

#include "include/Parser.h"
#include "include/ParseException.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Usage: katon <filepath>" << std::endl;
        return 0;
    }

    char* filename = argv[1];
    Object* object = nullptr;

    try {
        Parser parser(filename);
        object = parser.parse();
    }catch(ParseException& e) {
        std::cout << e.what() << std::endl;
    } catch(...) {
        std::cout << "Could not load file..." << std::endl;
    }

    delete object;

    return 0;
}
