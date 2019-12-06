#include <stdio.h>

#include "klex/Klex.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Usage: klex <filepath>\n");
        return 0;
    }

    char* filename = argv[1];
    
    try {
        Klex klex(filename);

        while(klex.nextToken()) {
            Token token = klex.getToken();
            printf("Token: %d - Line: %ld - Lexeme: %s\n", token.type, token.line, token.lexeme.c_str());
        }
    }catch(const char* e) {
        printf("%s\n", e);
    }

    return 0;
}
