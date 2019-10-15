#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "common_server.h"
#include <string>

/** Main
 *  @param port to run
 *  @param path to config file
 */
int main(int argc, char *argv[]) {
    try {
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
    } catch (std::exception &e) {
        printf("%s\n", e.what());
    }
}
