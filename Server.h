//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_SERVER_H
#define CMAKE_DEMO_SERVER_H


#include "Ftp.h"
#include "ServerMessages.h"

class Server {
private:
    Ftp ftp;
    ServerMessages msg;

public:
    Server();

    void run_server();

    std::string createFolder(char *folderName);

    ~Server();

    std::string getPwd();

    std::string getUnknownCommand();

    std::string getList();

    std::string removeDirectory(char *folderName);

    std::string quit();
};


#endif //CMAKE_DEMO_SERVER_H
