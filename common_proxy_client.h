//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_PROXY_CLIENT_H
#define CMAKE_DEMO_COMMON_PROXY_CLIENT_H


#include "common_socket.h"
#include "common_ftp.h"

class common_proxy_client {
private:
    Socket *skt;
    Socket sktA;
    common_ftp *ftp;

public:
    common_proxy_client(char *configPath, int port);

    std::string receive();

    void send(std::string response);

    ~common_proxy_client();
};


#endif //CMAKE_DEMO_COMMON_PROXY_CLIENT_H
