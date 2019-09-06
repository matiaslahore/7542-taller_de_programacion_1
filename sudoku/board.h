#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define BOARD_LENGTH 20

typedef struct {
    bool is_busy;
    unsigned short int value;
} cell_t;

typedef struct {
    cell_t cell[BOARD_LENGTH][BOARD_LENGTH];
} board_t;

typedef struct {
    int i;
    int j;
} position_t;

int board_load(board_t *board);

void board_print(board_t *board, char *board_buff);

bool board_is_busy(board_t *board, position_t position);

void board_insert_value(board_t *board, int value, position_t position);

bool board_has_rows_with_repeated_numbers(board_t *board);

bool board_has_columns_with_repeated_numbers(board_t *board);

bool board_has_boxes_with_repeated_numbers(board_t *board);

bool box_has_repeated_numbers(board_t *board, int start_i, int start_j);

#endif
