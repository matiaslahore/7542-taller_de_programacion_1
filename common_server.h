//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_SERVER_H
#define CMAKE_DEMO_COMMON_SERVER_H

#include "common_ftp.h"
#include "common_server_messages.h"
#include "common_login.h"

class common_server {
private:
    common_ftp sftp;
    common_server_messages *msg;
    common_login *slogin;

public:
    common_server();

    void run_server();

    std::string createFolder(char *folderName);

    std::string getPwd();

    std::string getUnknownCommand();

    std::string getList();

    std::string removeDirectory(char *folderName);

    std::string quit();

    std::string loginUser(char *userName);

    std::string loginPsw(char *psw);

    ~common_server();
};


#endif //CMAKE_DEMO_COMMON_SERVER_H
