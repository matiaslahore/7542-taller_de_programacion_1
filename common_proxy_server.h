//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_PROXY_SERVER_H
#define CMAKE_DEMO_COMMON_PROXY_SERVER_H

#include "common_socket.h"
#include <string>

class common_proxy_server {
private:
    Socket *skt;

public:
    common_proxy_server(char *host, int port);

    void send(std::string instruction);

    void receive();

    ~common_proxy_server();
};


#endif //CMAKE_DEMO_COMMON_PROXY_SERVER_H
