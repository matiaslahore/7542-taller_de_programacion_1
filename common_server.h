//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_SERVER_H
#define CMAKE_DEMO_COMMON_SERVER_H

#include "common_ftp.h"
#include "common_server_messages.h"
#include "common_login.h"
#include "common_proxy_client.h"
#include "Thread.h"
#include "common_acceptor.h"

class common_server : public Thread {
private:
    common_proxy_client *client;
    Socket *skt;
    common_ftp *ftp;
    common_acceptor *acceptor;

public:
    common_server(char *port, char *configPath);

    virtual void run();

    void stop();

    ~common_server();
};


#endif //CMAKE_DEMO_COMMON_SERVER_H
