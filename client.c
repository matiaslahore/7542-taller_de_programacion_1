#include <string.h>
#include <stdio.h>
#include <errno.h>

#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "socket.h"

#define REQUEST_MAX_LEN 128
#define RESPONSE_MAX_LEN 1024
#define PORT 80

int main(int argc, char *argv[]) {
    const char *hostname = "localhost";

    const char *request = "Hola Mundo";
    int request_len;

    request_len = strlen(request);

    socket_t skt;
    socket_create(&skt);
    socket_connect(&skt, hostname, PORT);

    socket_send(&skt, request, request_len);

    printf("\n");
    shutdown(skt.skt, SHUT_RDWR);
    close(skt.skt);


    return 0;
}

