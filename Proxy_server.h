//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_PROXY_SERVER_H
#define CMAKE_DEMO_PROXY_SERVER_H


#include "Proxy.h"

class Proxy_server {
private:
    Proxy proxy;
public:
    Proxy_server();

    void send_instruction(char *instruction);

    ~Proxy_server();
};


#endif //CMAKE_DEMO_PROXY_SERVER_H
