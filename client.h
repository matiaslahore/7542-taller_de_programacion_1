#ifndef CLIENT_H
#define CLIENT_H

#include "socket.h"

int client_run(char *hostname, char *port);

int client_init(socket_t *skt, char *hostname, char *port);

void client_loop(socket_t *skt);

#endif