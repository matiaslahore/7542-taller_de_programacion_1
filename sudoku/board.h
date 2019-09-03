#ifndef BOARD_H
#define BOARD_H

#define BOARD_LENGTH 20

typedef struct {
    bool busy;
    int value;
} cell_t;

typedef struct {
    cell_t cell[BOARD_LENGTH][BOARD_LENGTH];
} board_t;

int load_board();

int create_board();

#endif