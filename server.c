#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"
#include "socket.h"
#include "protocol.h"
#include "server.h"

#define MAX_BUFFER_COMMUNICATION_LEN 723
#define HOSTNAME "localhost"

int server_run(char *port) {
    sudoku_t sudoku;

    socket_t skt;
    socket_t skt_accepted;

    sudoku_game_load(&sudoku);
    server_init(&skt, &skt_accepted, port);
    return server_loop(&sudoku, &skt, &skt_accepted);
}

int server_init(socket_t *skt, socket_t *skt_accepted, char *port) {
    socket_create(skt);
    socket_bind_and_listen(skt, HOSTNAME, port);
    socket_accept(skt, skt_accepted);

    return 0;
}

int server_loop(sudoku_t *sudoku, socket_t *skt, socket_t *skt_accepted) {
    bool continue_running = true;
    int len = 0;
    char answer_len[4] = "";

    while (continue_running) {
        char answer[MAX_BUFFER_COMMUNICATION_LEN] = "";
        char command[1] = "";
        socket_receive(skt_accepted, command, 1);

        len = strlen(command);
        if (len == 0) continue_running = false;
        protocol_get_instruction(sudoku, command, answer, skt_accepted);
        snprintf(answer_len, sizeof(answer_len), "%zu", strlen(answer));
        socket_send(skt_accepted, answer_len, 4);
        socket_send(skt_accepted, answer, MAX_BUFFER_COMMUNICATION_LEN);
    }

    return 0;
}
