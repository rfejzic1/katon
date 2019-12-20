#include <iostream>

#include "include/Parser.h"
#include "include/ParseException.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Usage: katon <filepath>" << std::endl;
        return 0;
    }

    char* filename = argv[1];
    AbstractSyntaxTree* abs = nullptr;

    try {
        Parser parser(filename);
        abs = parser.parse();
    }catch(ParseException& e) {
        std::cout << e.what() << std::endl;
    }

    delete abs;

    return 0;
}
