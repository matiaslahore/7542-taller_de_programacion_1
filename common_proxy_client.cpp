//
// Created by mati on 25/9/19.
//

#include <cstring>
#include <string>
#include "common_proxy_client.h"

#define MKD_COMMAND "MKD"
#define PWD_COMMAND "PWD"
#define LIST_COMMAND "LIST"
#define RMD_COMMAND "RMD"
#define QUIT_COMMAND "QUIT"
#define LOGIN_USER_COMMAND "USER"
#define LOGIN_PSW_COMMAND "PASS"

common_proxy_client::common_proxy_client(common_ftp *ftp, Socket *skt) {
    this->ftp = ftp;
    this->skt = skt;
}

void common_proxy_client::run() {
    std::string response;

    while (!exit) {
        response = this->receive();
        this->send(response);
    }
}

std::string common_proxy_client::receive() {
    char instruction[10] = "";
    this->skt->receive(instruction, sizeof(instruction));

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

void common_proxy_client::send(const std::string &response) {
    this->skt->send(response.c_str(), strlen(response.c_str()));
}

bool common_proxy_client::is_dead() {
    return this->exit;
}

void common_proxy_client::stop() {
    this->skt->shutdown();
    this->exit = true;
}

common_proxy_client::~common_proxy_client() {
    if (!this->exit)
        this->skt->shutdown();
    delete this->skt;
}
