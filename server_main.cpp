#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "common_server.h"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("faltan argumentos");
        return 0;
    }

    common_server *server = new common_server(argv[1], argv[2]);
    server->run_server();
    delete server;

    return 0;
}
