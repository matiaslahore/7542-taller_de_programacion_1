//
// Created by mati on 25/9/19.
//

#include <string>
#include <iostream>
#include "common_server.h"
#include "common_server_messages.h"

common_server::common_server() {
    char configPath[20] = "config.cfg";
    this->msg = new common_server_messages(configPath);
    this->slogin = new common_login(this->msg->getUsername(), this->msg->getPassword());
}

void common_server::run_server() {
    bool exit = false;
    std::string str;

    while (!exit) {
        std::getline(std::cin, str);
        //if str = quit stop server, exit = true

        exit = false;
    }
}

std::string common_server::createFolder(char *folderName) {
    if (!this->slogin->isLogged()) return this->msg->getLoginRequired();
    if (this->sftp.newFolder(folderName))
        return this->msg->getMkdSuccess(folderName);

    return this->msg->getMkdFail();
}

std::string common_server::getPwd() {
    if (!this->slogin->isLogged()) return this->msg->getLoginRequired();
    return this->msg->getPwdSuccess();
}

std::string common_server::getUnknownCommand() {
    return this->msg->getUnknownCommand();
}

std::string common_server::getList() {
    if (!this->slogin->isLogged()) return this->msg->getLoginRequired();
    return this->msg->getListFolders(this->sftp.listFolders());
}

std::string common_server::removeDirectory(char *folderName) {
    if (!this->slogin->isLogged()) return this->msg->getLoginRequired();
    if (this->sftp.removeFolder(folderName))
        return this->msg->getRemoveSuccess();

    return this->msg->getRemoveFail();
}

std::string common_server::quit() {
    return this->msg->getQuit();
}

std::string common_server::loginUser(char *userName) {
    this->slogin->loginUser(userName);
    return this->msg->getPswRequired();
}

std::string common_server::loginPsw(char *psw) {
    if (this->slogin->loginPsw(psw))
        return this->msg->getLoginSuccess();

    return this->msg->getLoginFail();
}

common_server::~common_server() {
    delete this->slogin;
    delete this->msg;
}