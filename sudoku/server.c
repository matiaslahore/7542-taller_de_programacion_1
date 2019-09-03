#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "game.h"

int run_server(char *port) {

    server_init_game();
    server_init(atoi(port));
    return 0;
}

int server_init(int port) {
    return 0;
}

int server_init_game() {
    game_load();
    return ();
}

int start_socket(int port) {
    return 0;
}

int run_game() {
    return 0;
}
