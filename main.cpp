#include "include/Parser.h"
#include "include/ParseException.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Usage: katon <filepath>\n");
        return 0;
    }

    char* filename = argv[1];
    
    try {
        Parser parser(filename);
        AbstractSyntaxTree* abs = parser.parse();

        delete abs;
    }catch(ParseException& e) {
        printf("%s\n", e.what());
    }

    return 0;
}
