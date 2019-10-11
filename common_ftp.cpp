//
// Created by mati on 25/9/19.
//

#include <string>
#include "common_ftp.h"


common_ftp::common_ftp(char *configPath) {
    this->msg = new common_server_messages(configPath);
    std::string username = this->msg->getUsername();
    std::string password = this->msg->getPassword();
    this->login = new common_login(username, password);
}

common_ftp::~common_ftp() {
    delete this->msg;
    delete this->login;
}

std::string common_ftp::createFolder(char *folderName) {
    if (!this->login->isLogged()) return this->msg->getLoginRequired();
    if (this->dir.createFolder(folderName))
        return this->msg->getMkdSuccess(folderName);

    return this->msg->getMkdFail();
}

std::string common_ftp::getPwd() {
    if (!this->login->isLogged()) return this->msg->getLoginRequired();
    return this->msg->getPwdSuccess();
}

std::string common_ftp::getUnknownCommand() {
    return this->msg->getUnknownCommand();
}

std::string common_ftp::getList() {
    if (!this->login->isLogged()) return this->msg->getLoginRequired();
    return this->msg->getListFolders(this->dir.listFolders());
}

std::string common_ftp::removeDirectory(char *folderName) {
    if (!this->login->isLogged()) return this->msg->getLoginRequired();
    if (this->dir.removeFolder(folderName))
        return this->msg->getRemoveSuccess();

    return this->msg->getRemoveFail();
}

std::string common_ftp::quit() {
    return this->msg->getQuit();
}

std::string common_ftp::loginUser(std::string userName) {
    this->login->loginUser(userName);
    return this->msg->getPswRequired();
}

std::string common_ftp::loginPsw(char *psw) {
    if (this->login->loginPsw(psw))
        return this->msg->getLoginSuccess();

    return this->msg->getLoginFail();
}