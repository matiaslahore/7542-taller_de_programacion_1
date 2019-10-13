//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_FTP_H
#define CMAKE_DEMO_COMMON_FTP_H


#include <string>
#include "common_directory.h"
#include "common_server_messages.h"
#include "common_login.h"

class common_ftp {
private:
    common_directory dir;
    common_server_messages *msg;

public:
    common_ftp(char *configPath);

    ~common_ftp();

    std::string createFolder(const std::string &folderName);

    std::string getPwd();

    std::string getUnknownCommand();

    std::string getList();

    std::string removeDirectory(const std::string &folderName);

    std::string quit();

    std::string getUserName();

    std::string getPassword();

    std::string getLoginRequired();

    std::string getPswRequired();

    std::string getLoginSuccess();

    std::string getLoginFail();
};


#endif //CMAKE_DEMO_COMMON_FTP_H
