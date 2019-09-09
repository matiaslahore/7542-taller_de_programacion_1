#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "socket.h"
#include "protocol.h"
#include "client.h"

#define MAX_BUFFER_COMMUNICATION_LEN 723

int client_run(char *hostname, char *port) {
    socket_t skt;
    client_init(&skt, hostname, port);
    client_loop(&skt);

    return 0;
}

int client_init(socket_t *skt, char *hostname, char *port) {
    socket_create(skt);
    socket_connect(skt, hostname, port);

    return 0;
}

void client_loop(socket_t *skt) {
    bool continue_running = true;
    char input[15];
    char answer[MAX_BUFFER_COMMUNICATION_LEN] = "";

    while (continue_running) {
        if (fgets(input, sizeof(input), stdin)) {
            char query[4] = "";
            char error[50] = "";
            int response = protocol_client_command_to_message(input, query, skt, error);
            if (response == 0) {
                socket_send(skt, query, strlen(query));
                socket_receive(skt, answer, MAX_BUFFER_COMMUNICATION_LEN);
                printf("%s", answer);
                if (strlen(answer) == 0) continue_running = false;
            } else if (response == 1) {
                fprintf(stderr, "%s", error);
            } else if (response == -1) {
                continue_running = false;
            }
        }
    }
}
