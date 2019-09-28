//
// Created by mati on 27/9/19.
//

#include "ServerMessages.h"
#include <utility>

ServerMessages::ServerMessages() {
    this->messages.insert({MKD_SUCCESS_MESSAGE, "created"});
    this->messages.insert({MKD_FAIL_MESSAGE, "Create Directory operation failed"});
    this->messages.insert({UNKNOWN_COMMAND_MESSAGE, "Unknown command."});
    this->messages.insert({PWD_SUCCESS_MESSAGE, "\"/home/admin/ftp\" is the current directory."});
    this->messages.insert({LIST_DIR_START_MESSAGE, "Here comes the directory listing."});
    this->messages.insert({LIST_DIR_END_MESSAGE, "Directory send OK."});
    this->messages.insert({RMD_SUCCESS_MESSAGE, "Remove directory operation successful."});
    this->messages.insert({RMD_FAIL_MESSAGE, "Remove directory operation failed."});
    this->messages.insert({QUIT_SUCCESS_MESSAGE, "Goodbye."});
    this->messages.insert({PSW_REQ_MESSAGE, "Please specify the password."});
    this->messages.insert({LOGIN_SUCCESS_MESSAGE, "Login successful."});
    this->messages.insert({LOGIN_FAIL_MESSAGE, "Login incorrect."});
    this->messages.insert({LOGIN_REQ_MESSAGE, "Please login with USER and PASS."});
}

std::string ServerMessages::createMessage(const std::string &key, std::string pre, const std::string &post) {
    std::string msg = std::move(pre);
    msg += this->messages.at(key);
    msg += post;

    return msg;
}

std::string ServerMessages::getMkdSuccess(const std::string &foldName) {
    std::string pre = SUCCESS_CODE;
    pre += "\"" + foldName + "\" ";
    return this->createMessage(MKD_SUCCESS_MESSAGE, pre, "");
}

std::string ServerMessages::getMkdFail() {
    std::string pre = FAIL_CODE;
    return this->createMessage(MKD_FAIL_MESSAGE, pre, "");
}

std::string ServerMessages::getUnknownCommand() {
    std::string pre = UNKNOWN_COMMAND_CODE;
    return this->createMessage(UNKNOWN_COMMAND_MESSAGE, pre, "");
}

std::string ServerMessages::getPwdSuccess() {
    std::string pre = SUCCESS_CODE;
    return this->createMessage(PWD_SUCCESS_MESSAGE, pre, "");
}

std::string ServerMessages::getListFolders(const std::string &folders) {
    std::string pre = LIST_DIR_START_CODE;
    std::string response = this->createMessage(LIST_DIR_START_MESSAGE, pre, "") + "\n";
    response += folders;
    std::string pre2 = LIST_DIR_END_CODE;
    response += this->createMessage(LIST_DIR_END_MESSAGE, pre2, "");
    return response;
}

std::string ServerMessages::getRemoveSuccess() {
    std::string pre = SUCCESS_RMD_CODE;
    return this->createMessage(RMD_SUCCESS_MESSAGE, pre, "");
}

std::string ServerMessages::getRemoveFail() {
    std::string pre = FAIL_CODE;
    return this->createMessage(RMD_FAIL_MESSAGE, pre, "");
}

std::string ServerMessages::getQuit() {
    std::string pre = QUIT_SUCCESS_CODE;
    return this->createMessage(QUIT_SUCCESS_MESSAGE, pre, "");
}

std::string ServerMessages::getPswRequired() {
    std::string pre = PSW_REQ_CODE;
    return this->createMessage(PSW_REQ_MESSAGE, pre, "");
}

std::string ServerMessages::getLoginSuccess() {
    std::string pre = LOGIN_SUCCESS_CODE;
    return this->createMessage(LOGIN_SUCCESS_MESSAGE, pre, "");
}

std::string ServerMessages::getLoginFail() {
    std::string pre = LOGIN_FAIL_CODE;
    return this->createMessage(LOGIN_FAIL_MESSAGE, pre, "");
}

std::string ServerMessages::getLoginRequired() {
    std::string pre = LOGIN_FAIL_CODE;
    return this->createMessage(LOGIN_REQ_MESSAGE, pre, "");
}

ServerMessages::~ServerMessages() = default;
