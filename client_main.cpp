#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "common_client.h"

/** Main
 *  @param host of server
 *  @param port of server
 */
int main(int argc, char *argv[]) {
    try {
        if (argc < 3) {
            printf("faltan argumentos");
            return 1;
        }

        common_client client(argv[1], argv[2]);
        client.run_client();

        return 0;
    } catch (std::exception &e) {
        printf("ERROR DE EJECUCION:%s\n", e.what());
    }
}
