#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "sudoku.h"

void protocol_get_instruction(sudoku_t *sudoku, char *command, char *answer);

bool protocol_client_command_to_message(char *input, char *query);

#endif