//
// Created by mati on 12/10/19.
//

#include <vector>
#include "common_protocol.h"

common_protocol::common_protocol(common_ftp *ftp) : ftp(ftp) {
    this->interpreters[UKN_COMMAND] = new BaseProtocol(ftp);
    this->interpreters[LOGIN_USER_COMMAND] = new LoginUser(ftp);
    this->interpreters[LOGIN_PSW_COMMAND] = new LoginPass(ftp);
    this->interpreters[PWD_COMMAND] = new Pwd(ftp);
    this->interpreters[MKD_COMMAND] = new Mkd(ftp);
    this->interpreters[RMD_COMMAND] = new Rmd(ftp);
    this->interpreters[LIST_COMMAND] = new List(ftp);
    this->interpreters[QUIT_COMMAND] = new Quit(ftp);
}

common_protocol::~common_protocol() = default;

std::string common_protocol::executeCommand(const std::string &command,
                                            const std::vector<char>& data) {
    std::string result;
    result = this->interpreters.at(command)->execute(data);
    if (result.empty()) result = this->interpreters[UKN_COMMAND]->execute(data);

    return result;
}