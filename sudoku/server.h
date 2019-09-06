#ifndef SERVER_H
#define SERVER_H

int server_run(char *port);

int server_init(socket_t *skt, socket_t *skt_accepted, char *port);

int server_init_game(sudoku_t *sudoku);

void server_loop(sudoku_t *sudoku, socket_t *skt, socket_t *skt_accepted);

#endif