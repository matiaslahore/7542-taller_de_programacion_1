//
// Created by mati on 25/9/19.
//

#include "common_proxy_client.h"
#include <cstring>

#define MKD_COMMAND "MKD"
#define PWD_COMMAND "PWD"
#define LIST_COMMAND "LIST"
#define RMD_COMMAND "RMD"
#define QUIT_COMMAND "QUIT"
#define LOGIN_USER_COMMAND "USER"
#define LOGIN_PSW_COMMAND "PASS"

common_proxy_client::common_proxy_client() = default;

std::string common_proxy_client::send_command(char *instruction) {

    //recive un comando y llama a ejecutar algo al server
    if (strncmp(instruction, MKD_COMMAND, 3) == 0)
        return this->sserver.createFolder(&instruction[4]);
    else if (strncmp(instruction, PWD_COMMAND, 3) == 0)
        return this->sserver.getPwd();
    else if (strncmp(instruction, LIST_COMMAND, 4) == 0)
        return this->sserver.getList();
    else if (strncmp(instruction, RMD_COMMAND, 3) == 0)
        return this->sserver.removeDirectory(&instruction[4]);
    else if (strncmp(instruction, LOGIN_USER_COMMAND, 4) == 0)
        return this->sserver.loginUser(&instruction[5]);
    else if (strncmp(instruction, LOGIN_PSW_COMMAND, 4) == 0)
        return this->sserver.loginPsw(&instruction[5]);
    else if (strncmp(instruction, QUIT_COMMAND, 4) == 0)
        return this->sserver.quit();
    else
        return this->sserver.getUnknownCommand();

}

common_proxy_client::~common_proxy_client() = default;
