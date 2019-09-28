#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "Server.h"

int main(int argc, char *argv[]) {

    if (argc < 3){
        printf("faltan argumentos");
        return 0;
    }


    Server server;
    Server.run_server();

    return 0;
}
