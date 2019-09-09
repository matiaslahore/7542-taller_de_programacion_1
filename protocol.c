#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "sudoku.h"
#include "socket.h"
#include "protocol.h"

#define OK_MESSAGE "OK\n"
#define ERROR_MESSAGE "ERROR\n"
#define VALUE_ERROR "Error en el valor ingresado. Rango soportado: [1,9]\n"
#define INDEXES_ERROR "Error en los indices. Rango soportado: [1,9]\n"
#define NON_MODIFIABLE_CELL "La celda no es modificable\n"

void protocol_get_instruction(sudoku_t *sudoku, char *command, char *answer, socket_t *skt_accepted) {
    char verify[1] = "V";
    char reset[1] = "R";
    char get[1] = "G";
    char put[1] = "P";

    if (strncmp(command, verify, 1) == 0) {
        int ret = sudoku_verify_game(sudoku);
        strncpy(answer, (ret == 1) ? OK_MESSAGE : ERROR_MESSAGE, 10);
    } else if (strncmp(command, reset, 1) == 0) {
        sudoku_reset_game(sudoku);
        sudoku_get_board(sudoku, answer);
    } else if (strncmp(command, get, 1) == 0) {
        sudoku_get_board(sudoku, answer);
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

        if (sudoku_put_value(sudoku, value, position) != 0) {
            strncpy(answer, NON_MODIFIABLE_CELL, strlen(NON_MODIFIABLE_CELL));
        } else {
            sudoku_get_board(sudoku, answer);
        }
    }

}

int protocol_client_command_to_message(char *input, char *query, socket_t *skt, char *error) {
    char verify[6] = "verify";
    char reset[5] = "reset";
    char get[3] = "get";
    char exit[4] = "exit";
    char put[3] = "put";

    if (strncmp(input, verify, sizeof(verify)) == 0) {
        strncpy(query, "V", 1);
        return 0;
    } else if (strncmp(input, reset, sizeof(reset)) == 0) {
        strncpy(query, "R", 1);
        return 0;
    } else if (strncmp(input, get, sizeof(get)) == 0) {
        strncpy(query, "G", 1);
        return 0;
    } else if (strncmp(input, exit, sizeof(exit)) == 0) {
        socket_shutdown(skt);
    } else if (strncmp(input, put, sizeof(put)) == 0) {
        int verify = client_verify_put_range(&input[4]);

        if (verify == -1) {
            strncpy(error, VALUE_ERROR, strlen(VALUE_ERROR));
            return 1;
        } else if (verify == -2) {
            strncpy(error, INDEXES_ERROR, strlen(INDEXES_ERROR));
            return 1;
        }

        strncpy(query, "P", 1);
        strncat(query, &input[4], 1);
        strncat(query, &input[9], 1);
        strncat(query, &input[11], 1);;
        return 0;
    }

    return -1;
}

int client_verify_put_range(char *data) {
    char val_c[4] = "", i_c[4] = "", j_c[4] = "";

    memcpy(val_c, data, 1);
    memcpy(i_c, &data[5], 1);
    memcpy(j_c, &data[7], 1);

    int value = atoi(val_c);
    int pos_i = atoi(i_c);
    int pos_j = atoi(j_c);

    if (value < 1 || value > 9) return -1;
    else if (pos_i < 1 || pos_i > 9 || pos_j < 1 || pos_j > 9) return -2;
    else return 0;
}