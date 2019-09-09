#ifndef SERVER_H
#define SERVER_H

#include "socket.h"
#include "sudoku.h"

void server_run(char *port);

int server_init(socket_t *skt, socket_t *skt_accepted, char *port);

void server_init_game(sudoku_t *sudoku);

void server_loop(sudoku_t *sudoku, socket_t *skt, socket_t *skt_accepted);

void server_stop();

#endif