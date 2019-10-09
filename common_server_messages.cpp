//
// Created by mati on 27/9/19.
//

#include "common_server_messages.h"
#include <utility>
#include <sstream>
#include <map>
#include <string>

common_server_messages::common_server_messages(char *config) {
    this->readConfig(config);

    std::string value = this->getConfigValue(MKD_SUCCESS_MESSAGE);
    this->messages.insert({MKD_SUCCESS_MESSAGE,
                           !value.empty() ? value : DEF_MKD_SUCCESS_MESSAGE});
    value = this->getConfigValue(MKD_FAIL_MESSAGE);
    this->messages.insert({MKD_FAIL_MESSAGE,
                           !value.empty() ? value : DEF_MKD_FAIL_MESSAGE});
    value = this->getConfigValue(UNKNOWN_COMMAND_MESSAGE);
    this->messages.insert({UNKNOWN_COMMAND_MESSAGE,
                           !value.empty() ? value
                                          : DEF_UNKNOWN_COMMAND_MESSAGE});
    value = this->getConfigValue(PWD_SUCCESS_MESSAGE);
    this->messages.insert({PWD_SUCCESS_MESSAGE,
                           !value.empty() ? value : DEF_PWD_SUCCESS_MESSAGE});
    value = this->getConfigValue(LIST_DIR_START_MESSAGE);
    this->messages.insert({LIST_DIR_START_MESSAGE,
                           !value.empty() ? value : DEF_LIST_DIR_S_MESSAGE});
    value = this->getConfigValue(LIST_DIR_END_MESSAGE);
    this->messages.insert({LIST_DIR_END_MESSAGE,
                           !value.empty() ? value : DEF_LIST_DIR_END_MESSAGE});
    value = this->getConfigValue(RMD_SUCCESS_MESSAGE);
    this->messages.insert({RMD_SUCCESS_MESSAGE,
                           !value.empty() ? value : DEF_RMD_SUCCESS_MESSAGE});
    value = this->getConfigValue(RMD_FAIL_MESSAGE);
    this->messages.insert({RMD_FAIL_MESSAGE,
                           !value.empty() ? value : DEF_RMD_FAIL_MESSAGE});
    value = this->getConfigValue(QUIT_SUCCESS_MESSAGE);
    this->messages.insert({QUIT_SUCCESS_MESSAGE,
                           !value.empty() ? value : DEF_QUIT_SUCCESS_MESSAGE});
    value = this->getConfigValue(PSW_REQ_MESSAGE);
    this->messages.insert({PSW_REQ_MESSAGE,
                           !value.empty() ? value : DEF_PSW_REQ_MESSAGE});
    value = this->getConfigValue(LOGIN_SUCCESS_MESSAGE);
    this->messages.insert({LOGIN_SUCCESS_MESSAGE,
                           !value.empty() ? value : DEF_LOGIN_SUCCESS_MESSAGE});
    value = this->getConfigValue(LOGIN_FAIL_MESSAGE);
    this->messages.insert({LOGIN_FAIL_MESSAGE,
                           !value.empty() ? value : DEF_LOGIN_FAIL_MESSAGE});
    value = this->getConfigValue(LOGIN_REQ_MESSAGE);
    this->messages.insert({LOGIN_REQ_MESSAGE,
                           !value.empty() ? value : DEF_LOGIN_REQ_MESSAGE});
    value = this->getConfigValue(USERNAME);
    this->messages.insert({USERNAME,
                           !value.empty() ? value : DEF_USERNAME});
    value = this->getConfigValue(PASS);
    this->messages.insert({PASS, !value.empty() ? value : DEF_PASS});
}

std::string common_server_messages::getConfigValue(const std::string &key) {
    std::map<std::string, std::string>::iterator it;
    it = this->configValues.find(key);

    if (it != this->configValues.end())
        return it->second;

    return "";
}

void common_server_messages::readConfig(char *filePath) {
    std::fstream fin;
    fin.open(filePath, std::ifstream::in);
    std::string line;

    while (std::getline(fin, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (std::getline(is_line, value)) {
                this->configValues[key] = value;
            }
        }
    }
}

std::string common_server_messages::createMessage(const std::string &key,
                                                  std::string pre,
                                                  const std::string &post) {
    std::string msg = std::move(pre);
    msg += this->messages.at(key);
    msg += post;

    return msg;
}

std::string common_server_messages::getUsername() {
    return this->messages.at(USERNAME);
}

std::string common_server_messages::getPassword() {
    return this->messages.at(PASS);
}

std::string common_server_messages::getMkdSuccess(const std::string &foldName) {
    std::string pre = SUCCESS_CODE;
    pre += "\"" + foldName + "\" ";
    return this->createMessage(MKD_SUCCESS_MESSAGE, pre, "\n");
}

std::string common_server_messages::getMkdFail() {
    std::string pre = FAIL_CODE;
    return this->createMessage(MKD_FAIL_MESSAGE, pre, "\n");
}

std::string common_server_messages::getUnknownCommand() {
    std::string pre = UNKNOWN_COMMAND_CODE;
    return this->createMessage(UNKNOWN_COMMAND_MESSAGE, pre, "\n");
}

std::string common_server_messages::getPwdSuccess() {
    std::string pre = SUCCESS_CODE;
    return this->createMessage(PWD_SUCCESS_MESSAGE, pre, "\n");
}

std::string common_server_messages::getListFolders(const std::string &folders) {
    std::string pre = LIST_DIR_START_CODE;
    std::string response =
            this->createMessage(LIST_DIR_START_MESSAGE, pre, "") + "\n";
    response += folders;
    std::string pre2 = LIST_DIR_END_CODE;
    response += this->createMessage(LIST_DIR_END_MESSAGE, pre2, "\n");
    return response;
}

std::string common_server_messages::getRemoveSuccess() {
    std::string pre = SUCCESS_RMD_CODE;
    return this->createMessage(RMD_SUCCESS_MESSAGE, pre, "\n");
}

std::string common_server_messages::getRemoveFail() {
    std::string pre = FAIL_CODE;
    return this->createMessage(RMD_FAIL_MESSAGE, pre, "\n");
}

std::string common_server_messages::getQuit() {
    std::string pre = QUIT_SUCCESS_CODE;
    return this->createMessage(QUIT_SUCCESS_MESSAGE, pre, "\n");
}

std::string common_server_messages::getPswRequired() {
    std::string pre = PSW_REQ_CODE;
    return this->createMessage(PSW_REQ_MESSAGE, pre, "\n");
}

std::string common_server_messages::getLoginSuccess() {
    std::string pre = LOGIN_SUCCESS_CODE;
    return this->createMessage(LOGIN_SUCCESS_MESSAGE, pre, "\n");
}

std::string common_server_messages::getLoginFail() {
    std::string pre = LOGIN_FAIL_CODE;
    return this->createMessage(LOGIN_FAIL_MESSAGE, pre, "\n");
}

std::string common_server_messages::getLoginRequired() {
    std::string pre = LOGIN_FAIL_CODE;
    return this->createMessage(LOGIN_REQ_MESSAGE, pre, "\n");
}

common_server_messages::~common_server_messages() = default;
