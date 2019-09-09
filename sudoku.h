#ifndef SUDOKU_H
#define SUDOKU_H

#include "board.h"

typedef struct {
    board_t *board;
} sudoku_t;

void sudoku_create(sudoku_t *sudoku);

void sudoku_game_load(sudoku_t *sudoku);

void sudoku_get_board(sudoku_t *sudoku, char *board_buff);

int sudoku_put_value(sudoku_t *sudoku, int value, position_t position);

void sudoku_reset_game(sudoku_t *sudoku);

int sudoku_verify_game(sudoku_t *sudoku);

void sudoku_destroy(sudoku_t *sudoku);

#endif