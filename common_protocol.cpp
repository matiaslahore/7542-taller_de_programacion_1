//
// Created by mati on 12/10/19.
//

#include <string>
#include <vector>
#include "common_protocol.h"

common_protocol::common_protocol(common_ftp *ftp) : ftp(ftp) {
    std::string username = this->ftp->getUserName();
    std::string password = this->ftp->getPassword();
    common_login *login = new common_login(username, password);
    this->interpreters[UKN_COMMAND] = new BaseProtocol(ftp, login);
    this->interpreters[LOGIN_USER_COMMAND] = new LoginUser(ftp, login);
    this->interpreters[LOGIN_PSW_COMMAND] = new LoginPass(ftp, login);
    this->interpreters[PWD_COMMAND] = new Pwd(ftp, login);
    this->interpreters[MKD_COMMAND] = new Mkd(ftp, login);
    this->interpreters[RMD_COMMAND] = new Rmd(ftp, login);
    this->interpreters[LIST_COMMAND] = new List(ftp, login);
    this->interpreters[QUIT_COMMAND] = new Quit(ftp, login);
    this->interpreters[HI_COMMAND] = new Hello(ftp, login);
    this->interpreters[SYS_COMMAND] = new SySInfo(ftp, login);
    this->interpreters[HELP_COMMAND] = new Help(ftp, login);
}

common_protocol::~common_protocol() = default;

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
