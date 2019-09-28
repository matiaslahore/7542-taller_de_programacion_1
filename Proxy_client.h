//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_PROXY_CLIENT_H
#define CMAKE_DEMO_PROXY_CLIENT_H


#include "Server.h"

class Proxy_client {
private:
    Server server;
public:
    Proxy_client();

    std::string send_command(char *instruction);

    ~Proxy_client();
};


#endif //CMAKE_DEMO_PROXY_CLIENT_H
