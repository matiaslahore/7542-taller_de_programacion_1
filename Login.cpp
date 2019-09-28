//
// Created by mati on 28/9/19.
//

#include "Login.h"

#include <utility>

Login::Login(std::string validUser, std::string validPsw) {
    this->validUser = std::move(validUser);
    this->validPsw = std::move(validPsw);
    this->logged = false;
}

void Login::loginUser(std::string user) {
    const std::string &strUser(user);
    this->user = strUser;
}

bool Login::loginPsw(std::string psw) {
    const std::string &strPsw(psw);
    if ((this->user == this->validUser) && (strPsw == this->validPsw))
        this->logged = true;

    return this->logged;
}

bool Login::isLogged() {
    return this->logged;
}

Login::~Login() = default;
