//
// Created by mati on 12/10/19.
//

#include <string>
#include <vector>
#include "common_protocol.h"

common_protocol::common_protocol(common_ftp *ftp) : ftp(ftp) {
    std::string username = this->ftp->getUserName();
    std::string password = this->ftp->getPassword();
    common_login *userLogin = new common_login(username, password);
    this->interpreters[UKN_COMMAND] = new BaseProtocol(ftp, userLogin);
    this->interpreters[LOGIN_USER_COMMAND] = new LoginUser(ftp, userLogin);
    this->interpreters[LOGIN_PSW_COMMAND] = new LoginPass(ftp, userLogin);
    this->interpreters[PWD_COMMAND] = new Pwd(ftp, userLogin);
    this->interpreters[MKD_COMMAND] = new Mkd(ftp, userLogin);
    this->interpreters[RMD_COMMAND] = new Rmd(ftp, userLogin);
    this->interpreters[LIST_COMMAND] = new List(ftp, userLogin);
    this->interpreters[QUIT_COMMAND] = new Quit(ftp, userLogin);
    this->interpreters[HI_COMMAND] = new Hello(ftp, userLogin);
    this->interpreters[SYS_COMMAND] = new SySInfo(ftp, userLogin);
    this->interpreters[HELP_COMMAND] = new Help(ftp, userLogin);
}

common_protocol::~common_protocol() {
    delete this->interpreters[UKN_COMMAND];
    delete this->interpreters[LOGIN_USER_COMMAND];
    delete this->interpreters[LOGIN_PSW_COMMAND];
    delete this->interpreters[PWD_COMMAND];
    delete this->interpreters[MKD_COMMAND];
    delete this->interpreters[RMD_COMMAND];
    delete this->interpreters[LIST_COMMAND];
    delete this->interpreters[QUIT_COMMAND];
    delete this->interpreters[HI_COMMAND];
    delete this->interpreters[SYS_COMMAND];
    delete this->interpreters[HELP_COMMAND];
}

std::string common_protocol::executeCommand(const std::string &command,
                                            const std::vector<char> &data) {
    std::string result;

    try {
        result = this->interpreters.at(command)->execute(data);
    } catch (...) {
        result = this->interpreters[UKN_COMMAND]->execute(data);
    }

    return result;
}

