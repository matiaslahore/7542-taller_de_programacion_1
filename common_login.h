//
// Created by mati on 28/9/19.
//

#ifndef CMAKE_DEMO_COMMON_LOGIN_H
#define CMAKE_DEMO_COMMON_LOGIN_H

#include <string>

class common_login {
private:
    std::string validUser;
    std::string validPsw;
    std::string user;
    bool logged;

public:
    common_login(std::string validUser, std::string validPsw);

    void loginUser(std::string user);

    bool loginPsw(std::string psw);

    bool isLogged();

    ~common_login();
};


#endif //CMAKE_DEMO_COMMON_LOGIN_H
