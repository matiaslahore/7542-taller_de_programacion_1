#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "sudoku.h"

int run_server(char *port) {

    server_init_game();
    server_init(atoi(port));
    return 0;
}

int server_init(int port) {
    return 0;
}

int server_init_game() {
    sudoku_t sudoku;
    return sudoku_game_load(&sudoku);
}

int run_game() {
    return 0;
}
