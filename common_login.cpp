//
// Created by mati on 28/9/19.
//

#include "common_login.h"

#include <utility>

common_login::common_login(std::string validUser, std::string validPsw) {
    this->validUser = std::move(validUser);
    this->validPsw = std::move(validPsw);
    this->logged = false;
}

void common_login::loginUser(std::string user) {
    const std::string &strUser(user);
    this->user = strUser;
}

bool common_login::loginPsw(std::string psw) {
    const std::string &strPsw(psw);
    if ((this->user == this->validUser) && (strPsw == this->validPsw))
        this->logged = true;

    return this->logged;
}

bool common_login::isLogged() {
    return this->logged;
}

common_login::~common_login() = default;
