//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_PROXY_CLIENT_H
#define CMAKE_DEMO_COMMON_PROXY_CLIENT_H


#include "common_server.h"

class common_proxy_client {
private:
    common_server sserver;
public:
    common_proxy_client();

    std::string send_command(char *instruction);

    ~common_proxy_client();
};


#endif //CMAKE_DEMO_COMMON_PROXY_CLIENT_H
