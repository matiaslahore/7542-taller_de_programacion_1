#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "sudoku.h"

void sudoku_create(sudoku_t *sudoku) {
    sudoku->board = malloc(sizeof(board_t));
}

void sudoku_game_load(sudoku_t *sudoku) {
    board_load(sudoku->board);
}

void sudoku_get_board(sudoku_t *sudoku, char *board_buff) {
    board_print(sudoku->board, board_buff);
}

int sudoku_put_value(sudoku_t *sudoku, int value, position_t position) {
    if (board_is_busy(sudoku->board, position)) return -1;
    board_insert_value(sudoku->board, value, position);
    return 0;
}

void sudoku_reset_game(sudoku_t *sudoku) {
    board_load(sudoku->board);
}

int sudoku_verify_game(sudoku_t *sudoku) {
    if (board_has_rows_with_repeated_numbers(sudoku->board) ||
        board_has_columns_with_repeated_numbers(sudoku->board) ||
        board_has_boxes_with_repeated_numbers(sudoku->board)) {
        return -1;
    }

    return 1;
}

void sudoku_destroy(sudoku_t *sudoku){
    free(sudoku->board);
}