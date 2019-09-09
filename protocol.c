#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"

#define MAX_ANSWER_LEN 180
#define OK_MESSAGE "OK\n"
#define ERROR_MESSAGE "ERROR\n"


void protocol_get_instruction(sudoku_t *sudoku, char *command, char *answer) {
    char verify[1] = "V";
    char reset[1] = "R";
    char get[1] = "G";
    char exit[1] = "G";
    //char put[1] = "P";

    if (strncmp(command, verify, sizeof(char)) == 0) {
        int ret = sudoku_verify_game(sudoku);
        strncpy(answer, (ret == 1) ? OK_MESSAGE : ERROR_MESSAGE, 10);
    } else if (strncmp(command, reset, sizeof(char)) == 0) {
        sudoku_reset_game(sudoku);
        sudoku_get_board(sudoku, answer);
    } else if (strncmp(command, get, sizeof(char)) == 0) {
        sudoku_get_board(sudoku, answer);
    } else if (strncmp(command, exit, sizeof(char)) == 0) {
        sudoku_destroy(sudoku);
    }

}

bool protocol_client_command_to_message(char *input, char *query) {
    char verify[6] = "verify";
    char reset[5] = "reset";
    char get[3] = "get";
    char exit[4] = "exit";
    char put[3] = "put";

    if (strncmp(input, verify, sizeof(verify)) == 0) {
        strncpy(query, "V", 1);
        return true;
    } else if (strncmp(input, reset, sizeof(reset)) == 0) {
        strncpy(query, "R", 1);
        return true;
    } else if (strncmp(input, get, sizeof(get)) == 0) {
        strncpy(query, "G", 1);
        return true;
    } else if (strncmp(input, exit, sizeof(exit)) == 0) {
        strncpy(query, "E", 1);
        return true;
    } else if (strncmp(input, put, sizeof(put)) == 0) {
        strncpy(query, "P", 1);
        return true;
    }

    return false;
}