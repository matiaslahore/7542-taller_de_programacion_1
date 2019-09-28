//
// Created by mati on 25/9/19.
//

#include <string>
#include <iostream>
#include "Server.h"
#include "ServerMessages.h"

Server::Server() {
    this->login = new Login("a", "e");
}

void Server::run_server() {
    bool exit = false;
    std::string str;

    while (!exit) {
        std::getline(std::cin, str);
        //if str = quit stop server, exit = true

        exit = false;
    }
}

std::string Server::createFolder(char *folderName) {
    if (!this->login->isLogged()) return this->msg.getLoginRequired();
    if (this->ftp.newFolder(folderName))
        return this->msg.getMkdSuccess(folderName);

    return this->msg.getMkdFail();
}

std::string Server::getPwd() {
    if (!this->login->isLogged()) return this->msg.getLoginRequired();
    return this->msg.getPwdSuccess();
}

std::string Server::getUnknownCommand() {
    return this->msg.getUnknownCommand();
}

std::string Server::getList() {
    if (!this->login->isLogged()) return this->msg.getLoginRequired();
    return this->msg.getListFolders(this->ftp.listFolders());
}

std::string Server::removeDirectory(char *folderName) {
    if (!this->login->isLogged()) return this->msg.getLoginRequired();
    if (this->ftp.removeFolder(folderName))
        return this->msg.getRemoveSuccess();

    return this->msg.getRemoveFail();
}

std::string Server::quit() {
    return this->msg.getQuit();
}

std::string Server::loginUser(char *userName) {
    this->login->loginUser(userName);
    return this->msg.getPswRequired();
}

std::string Server::loginPsw(char *psw) {
    if (this->login->loginPsw(psw))
        return this->msg.getLoginSuccess();

    return this->msg.getLoginFail();
}

Server::~Server() {
    delete this->login;
}