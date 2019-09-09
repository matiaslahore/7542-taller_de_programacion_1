#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "board.h"

#define BOARD_PATH_FILE "board.txt"
#define BOARD_TEXT_DELIMITER " "
#define MAX_STR_BOARD_FILE 19
#define HEADER "U===========U===========U===========U\n"
#define INTER_LINE "U---+---+---U---+---+---U---+---+---U\n"
#define NUMBER_DIVISOR "|"

int board_load(board_t *board) {
    int i = 0;
    int row[9] = {0};
    char line[MAX_STR_BOARD_FILE];
    FILE *fb;
    fb = fopen(BOARD_PATH_FILE, "r");

    if (fb == NULL) return -1;

    while (fgets(line, MAX_STR_BOARD_FILE, fb) != NULL) {
        sscanf(line, "%d %d %d %d %d %d %d %d %d", &row[0], &row[1],
               &row[2], &row[3], &row[4], &row[5], &row[6], &row[7], &row[8]);
        for (int j = 0; j < 9; j++) {
            bool busy = (true ? (row[j] != 0) : false);
            cell_t cell = {.value = row[j], .is_busy = busy};
            board->cell[i][j] = cell;
        }
        i++;
    }

    fclose(fb);

    return 0;
}

bool board_is_busy(board_t *board, position_t position) {
    return board->cell[position.i][position.j].is_busy;
}

void board_insert_value(board_t *board, int value, position_t position) {
    board->cell[position.i][position.j].value = value;
}

void board_print(board_t *board, char *board_buff) {
    unsigned short int cell_value = 0;
    char value_c[4];

    strncat(board_buff, HEADER, strlen(HEADER));

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cell_value = board->cell[i][j].value;
            if (cell_value != 0)
                snprintf(value_c, sizeof(value_c), " %d ", cell_value);
            else
                strncpy(value_c, "   ", 4);
            if ((j % 3) == 0)
                strncat(board_buff, "U", sizeof(char));
            else
                strncat(board_buff, "|", sizeof(char));
            strncat(board_buff, value_c, 4);
        }
        strncat(board_buff, "U\n", 2);
        if (((i + 1) % 3) == 0)
            strncat(board_buff, HEADER, strlen(HEADER));
        else
            strncat(board_buff, INTER_LINE, strlen(HEADER));
    }
}

bool board_has_rows_with_repeated_numbers(board_t *board) {
    int value = 0;

    for (int i = 0; i < 9; i++) {
        unsigned short int sum[BOARD_LENGTH] = {0};
        for (int j = 0; j < 9; j++) {
            value = board->cell[i][j].value;
            if (value == 0) continue; //salto los ceros
            sum[value]++;
            if (sum[value] > 1) return true;
        }
    }

    return false;
}

bool board_has_columns_with_repeated_numbers(board_t *board) {
    int value = 0;

    for (int i = 0; i < 9; i++) {
        unsigned short int sum[BOARD_LENGTH] = {0};
        for (int j = 0; j < 9; j++) {
            value = board->cell[j][i].value;
            if (value == 0) continue; //salto los ceros
            sum[value]++;
            if (sum[value] > 1) return true;
        }
    }


    return false;
}

bool board_has_boxes_with_repeated_numbers(board_t *board) {
    return box_has_repeated_numbers(board, 0, 0) ||
           box_has_repeated_numbers(board, 0, 3) ||
           box_has_repeated_numbers(board, 0, 6) ||
           box_has_repeated_numbers(board, 3, 0) ||
           box_has_repeated_numbers(board, 3, 3) ||
           box_has_repeated_numbers(board, 3, 6) ||
           box_has_repeated_numbers(board, 6, 0) ||
           box_has_repeated_numbers(board, 6, 3) ||
           box_has_repeated_numbers(board, 6, 6);
}

bool box_has_repeated_numbers(board_t *board, int start_i, int start_j) {
    int value = 0;
    int end_i = start_i + 3;
    int end_j = start_j + 3;
    unsigned short int sum[BOARD_LENGTH] = {0};

    for (int i = start_i; i < end_i; i++) {
        for (int j = start_j; j < end_j; j++) {
            value = board->cell[j][i].value;
            if (value == 0) continue; //salto los ceros
            sum[value]++;
            if (sum[value] > 1) return true;
        }
    }

    return false;
}
