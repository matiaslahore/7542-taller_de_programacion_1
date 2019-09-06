#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "sudoku.h"
#include "server.h"

#define MAX_BUFFER_COMMUNICATION_LEN 180

int server_run(char *port) {

    sudoku_t sudoku;
    socket_t skt;
    socket_t skt_accepted;

    server_init_game(&sudoku);
    server_init(&skt, &skt_accepted, port);

    server_loop(&sudoku, &skt, &skt_accepted);
    return 0;
}

int server_init(socket_t *skt, socket_t *skt_accepted, char *port) {

    socket_create(skt);
    socket_bind_and_listen(skt, "localhost", port);
    socket_accept(skt, skt_accepted);

    return 0;
}

int server_init_game(sudoku_t *sudoku) {
    return sudoku_game_load(sudoku);
}

void server_loop(sudoku_t *sudoku, socket_t *skt, socket_t *skt_accepted) {
    bool continue_running = true;
    int len = 0;
    char buffer_communication[MAX_BUFFER_COMMUNICATION_LEN];

    while (continue_running) {
        memset(buffer_communication, 0, MAX_BUFFER_COMMUNICATION_LEN);
        socket_receive(skt_accepted, buffer_communication, MAX_BUFFER_COMMUNICATION_LEN - 1);

        printf("buffer_com: %s \n", buffer_communication);

        len = strlen(buffer_communication);
        printf("recive %i bytes\n", len);

        if (len == 0) continue_running = false;

        printf("Sent %i/%i bytes\n\n", socket_send(skt, buffer_communication, len), len);
    }
}
