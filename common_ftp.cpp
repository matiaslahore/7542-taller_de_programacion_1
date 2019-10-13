//
// Created by mati on 25/9/19.
//

#include <string>
#include "common_ftp.h"


common_ftp::common_ftp(char *configPath) {
    this->msg = new common_server_messages(configPath);
    std::string username = this->msg->getUsername();
    std::string password = this->msg->getPassword();
}

common_ftp::~common_ftp() {
    delete this->msg;
}

std::string common_ftp::getUserName() {
    return this->msg->getUsername();
}

std::string common_ftp::getPassword() {
    return this->msg->getPassword();
}

std::string common_ftp::getLoginRequired() {
    return this->msg->getLoginRequired();
}

std::string common_ftp::getPswRequired() {
    return this->msg->getPswRequired();
}

std::string common_ftp::getLoginSuccess() {
    return this->msg->getLoginSuccess();
}

std::string common_ftp::getLoginFail() {
    return this->msg->getLoginFail();
}

std::string common_ftp::createFolder(const std::string &folderName) {
    if (this->dir.createFolder(folderName))
        return this->msg->getMkdSuccess(folderName);

    return this->msg->getMkdFail();
}

std::string common_ftp::getPwd() {
    return this->msg->getPwdSuccess();
}

std::string common_ftp::getUnknownCommand() {
    return this->msg->getUnknownCommand();
}

std::string common_ftp::getList() {
    return this->msg->getListFolders(this->dir.listFolders());
}

std::string common_ftp::removeDirectory(const std::string &folderName) {
    if (this->dir.removeFolder(folderName))
        return this->msg->getRemoveSuccess();

    return this->msg->getRemoveFail();
}

std::string common_ftp::quit() {
    return this->msg->getQuit();
}