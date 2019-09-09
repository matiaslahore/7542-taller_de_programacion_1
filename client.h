#ifndef CLIENT_H
#define CLIENT_H

struct socket_t;

int client_run(char *hostname, char *port);

int client_init(socket_t *skt, char *hostname, char *port);

int client_loop(socket_t *skt);

#endif