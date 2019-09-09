#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"
#include "server.h"
#include "socket.h"
#include "protocol.h"

#define MAX_BUFFER_COMMUNICATION_LEN 180

void server_run(char *port) {
    sudoku_t sudoku;
    sudoku_create(&sudoku);

    socket_t skt;
    socket_t skt_accepted;

    sudoku_game_load(&sudoku);
    server_init(&skt, &skt_accepted, port);
    server_loop(&sudoku, &skt, &skt_accepted);
    server_stop(&sudoku);
}

int server_init(socket_t *skt, socket_t *skt_accepted, char *port) {
    socket_create(skt);
    socket_bind_and_listen(skt, "localhost", port);
    socket_accept(skt, skt_accepted);

    return 0;
}

void server_loop(sudoku_t *sudoku, socket_t *skt, socket_t *skt_accepted) {
    bool continue_running = true;
    int len = 0;

    while (continue_running) {
        char answer[MAX_BUFFER_COMMUNICATION_LEN] = "";
        char command[1] = "";
        socket_receive(skt_accepted, command, 1);

        len = strlen(command);
        if (len == 0) continue_running = false;
        protocol_get_instruction(sudoku, command, answer, skt_accepted);
        socket_send(skt_accepted, answer, MAX_BUFFER_COMMUNICATION_LEN);
    }
}

void server_stop(sudoku_t *sudoku) {
    sudoku_destroy(sudoku);
}