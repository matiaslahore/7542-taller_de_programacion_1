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

common_proxy_client::common_proxy_client(char *configPath, int port) {
    this->skt = new Socket();
    this->ftp = new common_ftp(configPath);
    this->skt->bindAndListen(port);
    this->sktA = this->skt->accept();
}

std::string common_proxy_client::receive() {
    char instruction[10] = "";
    this->sktA.receive(instruction, sizeof(instruction));

    if (strncmp(instruction, MKD_COMMAND, 3) == 0)
        return this->ftp->createFolder(&instruction[4]);
    else if (strncmp(instruction, PWD_COMMAND, 3) == 0)
        return this->ftp->getPwd();
    else if (strncmp(instruction, LIST_COMMAND, 4) == 0)
        return this->ftp->getList();
    else if (strncmp(instruction, RMD_COMMAND, 3) == 0)
        return this->ftp->removeDirectory(&instruction[4]);
    else if (strncmp(instruction, LOGIN_USER_COMMAND, 4) == 0)
        return this->ftp->loginUser(&instruction[5]);
    else if (strncmp(instruction, LOGIN_PSW_COMMAND, 4) == 0)
        return this->ftp->loginPsw(&instruction[5]);
    else if (strncmp(instruction, QUIT_COMMAND, 4) == 0)
        return this->ftp->quit();
    else
        return this->ftp->getUnknownCommand();
}

void common_proxy_client::send(std::string response) {
    this->sktA.send(response.c_str(), strlen(response.c_str()));
}

common_proxy_client::~common_proxy_client() {
    delete this->skt;
    delete this->ftp;
}
