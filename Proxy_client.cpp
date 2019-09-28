//
// Created by mati on 25/9/19.
//

#include "Proxy_client.h"
#include <cstring>

#define MKD_COMMAND "MKD"
#define PWD_COMMAND "PWD"
#define LIST_COMMAND "LIST"
#define RMD_COMMAND "RMD"
#define QUIT_COMMAND "QUIT"
#define LOGIN_USER_COMMAND "USER"
#define LOGIN_PSW_COMMAND "PASS"

Proxy_client::Proxy_client() {}

std::string Proxy_client::send_command(char *instruction) {

    //recive un comando y llama a ejecutar algo al server
    if (strncmp(instruction, MKD_COMMAND, 3) == 0)
        return this->server.createFolder(&instruction[4]);
    else if (strncmp(instruction, PWD_COMMAND, 3) == 0)
        return this->server.getPwd();
    else if (strncmp(instruction, LIST_COMMAND, 4) == 0)
        return this->server.getList();
    else if (strncmp(instruction, RMD_COMMAND, 3) == 0)
        return this->server.removeDirectory(&instruction[4]);
    else if (strncmp(instruction, LOGIN_USER_COMMAND, 4) == 0)
        return this->server.loginUser(&instruction[5]);
    else if (strncmp(instruction, LOGIN_PSW_COMMAND, 4) == 0)
        return this->server.loginPsw(&instruction[5]);
    else if (strncmp(instruction, QUIT_COMMAND, 4) == 0)
        return this->server.quit();
    else
        return this->server.getUnknownCommand();

}

Proxy_client::~Proxy_client() {}
