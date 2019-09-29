//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_CLIENT_H
#define CMAKE_DEMO_COMMON_CLIENT_H

#include "common_proxy_server.h"

class common_client {
private:
    common_proxy_server proxyServer;

public:
    common_client();

    void run_client();

    ~common_client();
};


#endif //CMAKE_DEMO_COMMON_CLIENT_H
