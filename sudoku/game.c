#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

int load_game(char *port) {

    create_board();
    load_board();
    return 0;
}