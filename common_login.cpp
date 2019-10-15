//
// Created by mati on 28/9/19.
//

#include <string>
#include "common_login.h"

#include <utility>
#include <cstring>

/** Constructor
 *  @param validUser of system reference
 *  @param validPsw of system reference
 */
common_login::common_login(std::string &validUser, std::string &validPsw) {
    this->validUser = std::move(validUser);
    this->validPsw = std::move(validPsw);
    this->logged = false;
}

void common_login::loginUser(std::string &userLogin) {
    this->user = userLogin;
}

bool common_login::loginPsw(const std::string &psw) {
    if ((this->user == this->validUser) && (psw == this->validPsw))
        this->logged = true;

    return this->logged;
}

bool common_login::isLogged() {
    return this->logged;
}

common_login::~common_login() = default;
