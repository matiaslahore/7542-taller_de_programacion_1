//
// Created by mati on 12/10/19.
//

#ifndef CMAKE_DEMO_COMMON_PROTOCOL_H
#define CMAKE_DEMO_COMMON_PROTOCOL_H

#define MKD_COMMAND "MKD "
#define PWD_COMMAND "PWD "
#define LIST_COMMAND "LIST"
#define RMD_COMMAND "RMD "
#define QUIT_COMMAND "QUIT"
#define LOGIN_USER_COMMAND "USER"
#define LOGIN_PSW_COMMAND "PASS"
#define UKN_COMMAND "UCMD"

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
public:
    explicit BaseProtocol(common_ftp *ftp) : ftp(ftp) {};

    virtual std::string execute(std::vector<char> data) const {
        return this->ftp->getUnknownCommand();
    }
};

class LoginUser : public BaseProtocol {
public:
    explicit LoginUser(common_ftp *ftp) : BaseProtocol(ftp) {}

    std::string execute(std::vector<char> data) const override {
        std::string resp(data.begin() + 5, data.end());
        return this->ftp->loginUser(resp);
    }
};

class LoginPass : public BaseProtocol {
public:
    explicit LoginPass(common_ftp *ftp) : BaseProtocol(ftp) {}

    std::string execute(std::vector<char> data) const override {
        std::string resp(data.begin() + 5, data.end());
        return this->ftp->loginPsw(resp);
    }
};

class Pwd : public BaseProtocol {
public:
    explicit Pwd(common_ftp *ftp) : BaseProtocol(ftp) {}

    std::string execute(std::vector<char> data) const override {
        return this->ftp->getPwd();
    }
};

class Mkd : public BaseProtocol {
public:
    explicit Mkd(common_ftp *ftp) : BaseProtocol(ftp) {}

    std::string execute(std::vector<char> data) const override {
        std::string resp(data.begin() + 4, data.end());
        return this->ftp->createFolder(resp);
    }
};

class Rmd : public BaseProtocol {
public:
    explicit Rmd(common_ftp *ftp) : BaseProtocol(ftp) {}

    std::string execute(std::vector<char> data) const override {
        std::string resp(data.begin() + 4, data.end());
        return this->ftp->removeDirectory(resp);
    }
};

class List : public BaseProtocol {
public:
    explicit List(common_ftp *ftp) : BaseProtocol(ftp) {}

    std::string execute(std::vector<char> data) const override {
        return this->ftp->getList();
    }
};

class Quit : public BaseProtocol {
public:
    explicit Quit(common_ftp *ftp) : BaseProtocol(ftp) {}

    std::string execute(std::vector<char> data) const override {
        return this->ftp->quit();
    }
};


#endif //CMAKE_DEMO_COMMON_PROTOCOL_H
