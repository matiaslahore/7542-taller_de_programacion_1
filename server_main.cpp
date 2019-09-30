#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "common_server.h"

int main(int argc, char *argv[]) {

    if (argc < 3){
        printf("faltan argumentos");
        return 0;
    }

    common_server server;
    server.run_server();

    return 0;
}
