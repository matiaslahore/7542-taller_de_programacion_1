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
    common_login *login;

public:
    common_ftp(char *configPath);

    ~common_ftp();

    std::string createFolder(char *folderName);

    std::string getPwd();

    std::string getUnknownCommand();

    std::string getList();

    std::string removeDirectory(char *folderName);

    std::string quit();

    std::string loginUser(std::string userName);

    std::string loginPsw(char *psw);
};


#endif //CMAKE_DEMO_COMMON_FTP_H
