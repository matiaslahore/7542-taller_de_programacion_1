//
// Created by mati on 28/9/19.
//

#ifndef CMAKE_DEMO_LOGIN_H
#define CMAKE_DEMO_LOGIN_H

#include <string>


class Login {
private:

    std::string validUser;
    std::string validPsw;
    std::string user;
    bool logged;

public:
    Login(std::string validUser, std::string validPsw);

    void loginUser(std::string user);

    bool loginPsw(std::string psw);

    bool isLogged();

    ~Login();
};


#endif //CMAKE_DEMO_LOGIN_H
