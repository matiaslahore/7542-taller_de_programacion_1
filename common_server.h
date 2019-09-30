//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_SERVER_H
#define CMAKE_DEMO_COMMON_SERVER_H

#include "common_ftp.h"
#include "common_server_messages.h"
#include "common_login.h"
#include "common_proxy_client.h"

class common_server {
private:
    common_proxy_client *client;

public:
    common_server(char *port, char *configPath);

    void run_server();

    ~common_server();
};


#endif //CMAKE_DEMO_COMMON_SERVER_H
