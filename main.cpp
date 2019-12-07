#include "Parser/Parser.h"
#include "Common/ParseException.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Usage: klex <filepath>\n");
        return 0;
    }

    char* filename = argv[1];
    
    try {
        Parser parser(filename);
        AbstractSyntaxTree abs = parser.parse();
    }catch(ParseException& e) {
        printf("%s\n", e.what());
    }

    return 0;
}
