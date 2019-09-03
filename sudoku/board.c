#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "board.h"

#define BOARD_FILE "board.txt"
#define BOARD_TEXT_DELIMITER " "
#define MAX_STR_BOARD_FILE 20

int create_board() {
    board_t board;

    board = malloc(sizeof(board));

    load_board();
}

int load_board() {
    FILE *fb;
    char line[MAX_STR_BOARD_FILE];
    fb = fopen(BOARD_FILE, "r");

    if (fb == NULL) return -1;

    while (fgets(line, MAX_STR_BOARD_FILE, fb) != NULL) {
        char *ptr = strtok(line, " ");

        while (ptr != NULL) {
            printf("'%s'\n", ptr);
            ptr = strtok(NULL, " ");
        }

        printf("New line: \n");
    }

    fclose(fb);
    return 0;
}