#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "common_server.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("faltan argumentos");
        return 0;
    }
    common_server server(argv[1], argv[2]);
    server.start();

    std::string quit;
    while (true) {
        std::cin >> quit;
        if (quit == "q") break;
    }

    server.stop();
    server.join();

    return 0;
}
