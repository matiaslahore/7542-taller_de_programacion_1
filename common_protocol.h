//
// Created by mati on 12/10/19.
//

#ifndef CMAKE_DEMO_COMMON_PROTOCOL_H
#define CMAKE_DEMO_COMMON_PROTOCOL_H

#define MKD_COMMAND "MKD"
#define PWD_COMMAND "PWD"
#define LIST_COMMAND "LIST"
#define RMD_COMMAND "RMD"
#define QUIT_COMMAND "QUIT"
#define LOGIN_USER_COMMAND "USER"
#define LOGIN_PSW_COMMAND "PASS"
#define UKN_COMMAND "UCMD"
#define HI_COMMAND "CDHI"
#define SYS_COMMAND "SYST"
#define HELP_COMMAND "HELP"


#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
#include "common_ftp.h"

class BaseProtocol;

class common_protocol {
private:
    common_ftp *ftp;
    std::map<std::string, BaseProtocol *> interpreters;

public:
    explicit common_protocol(common_ftp *ftp);

    ~common_protocol();

    std::string
    executeCommand(const std::string &command, const std::vector<char> &data);
};

///////// INTERPRETERS /////////

class BaseProtocol {
protected:
    common_ftp *ftp;
    common_login *login;
public:
    explicit BaseProtocol(common_ftp *ftp, common_login *login) :
            ftp(ftp), login(login) {}

    virtual std::string execute(std::vector<char> data) const {
        return this->ftp->getUnknownCommand();
    }

    virtual ~BaseProtocol() = default;
};

class LoginUser : public BaseProtocol {
public:
    explicit LoginUser(common_ftp *ftp, common_login *login) :
            BaseProtocol(ftp, login) {}

    std::string execute(std::vector<char> data) const override {
        std::string userName(data.begin() + 5, data.end());
        this->login->loginUser(userName);
        return this->ftp->getPswRequired();
    }

    ~LoginUser() override = default;
};

class LoginPass : public BaseProtocol {
public:
    explicit LoginPass(common_ftp *ftp, common_login *login) :
            BaseProtocol(ftp, login) {}

    std::string execute(std::vector<char> data) const override {
        std::string psw(data.begin() + 5, data.end());
        if (this->login->loginPsw(psw))
            return this->ftp->getLoginSuccess();

        return this->ftp->getLoginFail();
    }

    ~LoginPass() override = default;
};

class Pwd : public BaseProtocol {
public:
    explicit Pwd(common_ftp *ftp, common_login *login) :
            BaseProtocol(ftp, login) {}

    std::string execute(std::vector<char> data) const override {
        if (!this->login->isLogged()) return this->ftp->getLoginRequired();
        return this->ftp->getPwd();
    }

    ~Pwd() override = default;
};

class Mkd : public BaseProtocol {
public:
    explicit Mkd(common_ftp *ftp, common_login *login) :
            BaseProtocol(ftp, login) {}

    std::string execute(std::vector<char> data) const override {
        if (!this->login->isLogged()) return this->ftp->getLoginRequired();
        std::string resp(data.begin() + 4, data.end());
        return this->ftp->createFolder(resp);
    }

    ~Mkd() override = default;
};

class Rmd : public BaseProtocol {
public:
    explicit Rmd(common_ftp *ftp, common_login *login) :
            BaseProtocol(ftp, login) {}

    std::string execute(std::vector<char> data) const override {
        if (!this->login->isLogged()) return this->ftp->getLoginRequired();
        std::string resp(data.begin() + 4, data.end());
        return this->ftp->removeDirectory(resp);
    }

    ~Rmd() override = default;
};

class List : public BaseProtocol {
public:
    explicit List(common_ftp *ftp, common_login *login) :
            BaseProtocol(ftp, login) {}

    std::string execute(std::vector<char> data) const override {
        if (!this->login->isLogged()) return this->ftp->getLoginRequired();
        return this->ftp->getList();
    }

    ~List() override = default;
};

class Quit : public BaseProtocol {
public:
    explicit Quit(common_ftp *ftp, common_login *login) :
            BaseProtocol(ftp, login) {}

    std::string execute(std::vector<char> data) const override {
        return this->ftp->quit();
    }

    ~Quit() override = default;
};

class Hello : public BaseProtocol {
public:
    explicit Hello(common_ftp *ftp, common_login *login) :
            BaseProtocol(ftp, login) {}

    std::string execute(std::vector<char> data) const override {
        return this->ftp->hello();
    }

    ~Hello() override = default;
};

class SySInfo : public BaseProtocol {
public:
    explicit SySInfo(common_ftp *ftp, common_login *login) :
            BaseProtocol(ftp, login) {}

    std::string execute(std::vector<char> data) const override {
        if (!this->login->isLogged()) return this->ftp->getLoginRequired();
        return this->ftp->getSysInfo();
    }

    ~SySInfo() override = default;
};

class Help : public BaseProtocol {
public:
    explicit Help(common_ftp *ftp, common_login *login) :
            BaseProtocol(ftp, login) {}

    std::string execute(std::vector<char> data) const override {
        if (!this->login->isLogged()) return this->ftp->getLoginRequired();
        return this->ftp->getHelp();
    }

    ~Help() override {
        delete this->login;
    }
};


#endif //CMAKE_DEMO_COMMON_PROTOCOL_H
