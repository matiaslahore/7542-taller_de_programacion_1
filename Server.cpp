//
// Created by mati on 25/9/19.
//

#include <string>
#include <iostream>
#include "Server.h"
#include "ServerMessages.h"

Server::Server() {

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
    if (this->ftp.newFolder(folderName))
        return this->msg.getMkdSuccess(folderName);

    return this->msg.getMkdFail();
}

std::string Server::getPwd() {
    return this->msg.getPwdSuccess();
}

std::string Server::getUnknownCommand() {
    return this->msg.getUnknownCommand();
}


Server::~Server() {

}

std::string Server::getList() {
    return this->msg.getListFolders(this->ftp.listFolders());
}

std::string Server::removeDirectory(char *folderName) {
    if (this->ftp.removeFolder(folderName))
        return this->msg.getRemoveSuccess();

    return this->msg.getRemoveFail();
}

std::string Server::quit() {
    return this->msg.getQuit();
}
