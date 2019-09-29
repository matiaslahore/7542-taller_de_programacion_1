//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_SERVER_H
#define CMAKE_DEMO_SERVER_H

#include "Ftp.h"
#include "ServerMessages.h"
#include "Login.h"

class Server {
private:
    Ftp ftp;
    ServerMessages *msg;
    Login *login;

public:
    Server();

    void run_server();

    std::string createFolder(char *folderName);

    std::string getPwd();

    std::string getUnknownCommand();

    std::string getList();

    std::string removeDirectory(char *folderName);

    std::string quit();

    std::string loginUser(char *userName);

    std::string loginPsw(char *psw);

    ~Server();
};


#endif //CMAKE_DEMO_SERVER_H
