//
// Created by mati on 22/8/19.
//

#include <stdio.h>

struct myStruct {
    int int1;
    char char1;
    int int2;
} ;

int main() {
    struct myStruct isLonger;

    printf("struct: %lu\n", sizeof(isLonger));
    printf("int1: %lu\n", sizeof(int));
    printf("char: %lu\n", sizeof(char));
    printf("int2: %lu\n", sizeof(int));
    return 0;
}
