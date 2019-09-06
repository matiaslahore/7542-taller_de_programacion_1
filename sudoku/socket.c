#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "socket.h"

int socket_create(socket_t *self) {
    self->skt = -1;
    return 0;
}

int socket_destroy(socket_t *self) {
    if (self->skt != -1) {
        close(self->skt);
    }
    return 0;
}

int socket_bind_and_listen(socket_t *self, const char *host_name, const char *port) {
    int s, val = 0;
    struct addrinfo hints;
    struct addrinfo *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE;     // AI_PASSIVE for server, 0 for client

    printf("port: %s \n", port);
    s = getaddrinfo(host_name, port, &hints, &ptr);

    if (s != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    self->skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (self->skt == -1) {
        printf("Error: %s\n", strerror(errno));
        freeaddrinfo(ptr);
        return 1;
    }

    //TIME_WAIT
    val = 1;
    s = setsockopt(self->skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (s == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->skt);
        freeaddrinfo(ptr);
        return 1;
    }

    //Direccion y puerto a escuchar
    s = bind(self->skt, ptr->ai_addr, ptr->ai_addrlen);
    if (s == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->skt);
        freeaddrinfo(ptr);
        return 1;
    }

    freeaddrinfo(ptr);

    // clientes en espera
    s = listen(self->skt, 20);
    if (s == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->skt);
        return 1;
    }

    return s;
}

int socket_connect(socket_t *self, const char *host_name, const char *port) {
    int s = 0;
    bool are_we_connected = false;
    struct addrinfo hints;
    struct addrinfo *result, *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    s = getaddrinfo(host_name, port, &hints, &result);

    if (s != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    for (ptr = result; ptr != NULL && are_we_connected == false; ptr = ptr->ai_next) {
        self->skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (self->skt == -1) {
            printf("Error: %s\n", strerror(errno));
        } else {
            s = connect(self->skt, ptr->ai_addr, ptr->ai_addrlen);
            if (s == -1) {
                printf("Error: %s\n", strerror(errno));
                close(self->skt);
            }
            are_we_connected = (s != -1);
        }
    }
    freeaddrinfo(result);

    if (are_we_connected == false) {
        return 1;
    }

    if (s == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->skt);
    }

    return s;
}

int socket_accept(socket_t *self, socket_t *accepted_socket) {
    int s = accept(self->skt, NULL, NULL);

    if (s == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->skt);
    } else {
        accepted_socket->skt = s;
    }

    return s;
}

int socket_receive(socket_t *self, char *buffer, size_t length) {
    int received = 0;
    int s = 0;
    bool is_the_socket_valid = true;
    char tmp[length];

    while (received < length && is_the_socket_valid) {
        s = recv(self->skt, &tmp[received], length - received, 0);



        if (s == 0) { // socket close
            is_the_socket_valid = false;
        } else if (s == -1) { // error
            is_the_socket_valid = false;
        } else {
            received += s;
            strncat(buffer, tmp, received);
        }
    }

    if (is_the_socket_valid) {
        return received;
    } else {
        shutdown(self->skt, SHUT_RDWR);
        close(self->skt);
        return -1;
    }
}

int socket_send(socket_t *self, const char *buffer, size_t length) {
    int sent = 0;
    int s = 0;
    bool is_the_socket_valid = true;

    while (sent < length && is_the_socket_valid) {
        s = send(self->skt, &buffer[sent], length - sent, MSG_NOSIGNAL);

        if (s == 0) {
            is_the_socket_valid = false;
        } else if (s == -1) {
            is_the_socket_valid = false;
        } else {
            sent += s;
        }
    }

    if (is_the_socket_valid) {
        return sent;
    } else {
        shutdown(self->skt, SHUT_RDWR);
        close(self->skt);
        return -1;
    }
}

void socket_shutdown(socket_t *self) {
    shutdown(self->skt, SHUT_RDWR);
    close(self->skt);
}