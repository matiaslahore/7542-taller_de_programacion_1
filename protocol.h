#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "sudoku.h"

struct socket_t;

void protocol_get_instruction(sudoku_t *sudoku, char *command, char *answer,
                              socket_t *skt_accepted);

int protocol_cli_cmd_to_msg(char *input, char *query, socket_t *skt,
                            char *error);

int protocol_client_verify_put_range(char *data);

#endif
