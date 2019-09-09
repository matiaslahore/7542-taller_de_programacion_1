#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "server.h"
#include "client.h"

#define MIN_PORT "0"
#define MAX_PORT "9999"
#define PE "Modo no soportado, el primer parametro debe ser server o client\n"
#define PARAMETER_SERVER_ERROR "Uso: ./tp server <puerto> \n"
#define PARAMETER_CLIENT_ERROR "Uso: ./tp client <host> <puerto> \n"

int port_valid(char *port) {
    int cmp_min = strncmp(port, MIN_PORT, 1);
    int cmp_max = strncmp(port, MAX_PORT, 4);
    int len = strlen(port);
    return ((cmp_min >= 0) && (cmp_max <= 0) && (len < 5));
}

int main(int argc, char *argv[]) {
    if ((argc < 2) || (argc > 4)) {
        printf("%s", PE);
        return 1;
    }

    if (!strncmp(argv[1], "server", 6)) {
        if ((argc < 3) || !port_valid(argv[2])) {
            printf("%s", PARAMETER_SERVER_ERROR);
            return 1;
        }
        return server_run(argv[2]);
    } else if (!strncmp(argv[1], "client", 5)) {
        if ((argc < 4) || !port_valid(argv[3])) {
            printf("%s", PARAMETER_CLIENT_ERROR);
            return 1;
        }
        return client_run(argv[2], argv[3]);
    } else {
        printf("%s", PE);
        return 1;
    }
}
