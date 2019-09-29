//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_PROXY_SERVER_H
#define CMAKE_DEMO_COMMON_PROXY_SERVER_H

#include "common_proxy.h"

class common_proxy_server {
private:
    common_proxy commonProxy;

public:
    common_proxy_server();

    void send_instruction(char *instruction);

    ~common_proxy_server();
};


#endif //CMAKE_DEMO_COMMON_PROXY_SERVER_H
