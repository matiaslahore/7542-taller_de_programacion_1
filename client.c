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

    char request[REQUEST_MAX_LEN];
    int request_len;
    char response[RESPONSE_MAX_LEN];
    int bytes_sent = 0;
    int bytes_recv = 0;

    snprintf(request, REQUEST_MAX_LEN, "Hola Mundo");
    request[REQUEST_MAX_LEN - 1] = 0;
    request_len = strlen(request);

    socket_t skt;
    socket_create(&skt);
    socket_connect(&skt, hostname, PORT);

    socket_send(&skt, &request[bytes_sent], request_len - bytes_sent);

    int receive = socket_receive(&skt, &response[bytes_recv], RESPONSE_MAX_LEN - bytes_recv - 1);

    printf("\n");

    if (receive != -1) {
        /* Le decimos a la otra maquina que cerramos la coneccion */
        shutdown(skt.skt, SHUT_RDWR);

        /* Cerramos el socket */
        close(skt.skt);
    } else {
        return 1;   // hubo un error, somos consistentes y salimos con un codigo de error
    }

    return 0;
}

