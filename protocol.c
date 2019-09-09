#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"
#include "socket.h"
#include "protocol.h"

#define MAX_ANSWER_LEN 180
#define OK_MESSAGE "OK\n"
#define ERROR_MESSAGE "ERROR\n"


void protocol_get_instruction(sudoku_t *sudoku, char *command, char *answer, socket_t *skt_accepted) {
    char verify[1] = "V";
    char reset[1] = "R";
    char get[1] = "G";
    char exit[1] = "E";
    char put[1] = "P";

    if (strncmp(command, verify, 1) == 0) {
        int ret = sudoku_verify_game(sudoku);
        strncpy(answer, (ret == 1) ? OK_MESSAGE : ERROR_MESSAGE, 10);
    } else if (strncmp(command, reset, 1) == 0) {
        sudoku_reset_game(sudoku);
        sudoku_get_board(sudoku, answer);
    } else if (strncmp(command, get, 1) == 0) {
        sudoku_get_board(sudoku, answer);
    } else if (strncmp(command, exit, 1) == 0) {
        sudoku_destroy(sudoku);
    } else if (strncmp(command, put, 1) == 0) {
        char data[3] = "", val_c[2] = "", i_c[2] = "", j_c[2] = "";
        socket_receive(skt_accepted, data, 3);

        memcpy(val_c, data, 1);
        memcpy(i_c, &data[1], 1);
        memcpy(j_c, &data[2], 1);

        unsigned short int value = atoi(val_c);
        unsigned short int pos_i = (atoi(i_c) - 1);
        unsigned short int pos_j = (atoi(j_c) - 1);
        position_t position = {.i =  pos_i, .j = pos_j};

        sudoku_put_value(sudoku, value, position);
        sudoku_get_board(sudoku, answer);
    }

}

bool protocol_client_command_to_message(char *input, char *query, socket_t *skt) {
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
        socket_shutdown(skt);
    } else if (strncmp(input, put, sizeof(put)) == 0) {
        strncpy(query, "P", 1);
        strncat(query, &input[4], 1);
        strncat(query, &input[9], 1);
        strncat(query, &input[11], 1);
        return true;
    }

    return false;
}