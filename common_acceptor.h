//
// Created by mati on 30/9/19.
//

#ifndef CMAKE_DEMO_COMMON_ACCEPTOR_H
#define CMAKE_DEMO_COMMON_ACCEPTOR_H

#include "Thread.h"
#include "vector"
#include "common_socket.h"
#include "common_ftp.h"
#include "common_proxy_client.h"

class common_acceptor : public Thread {
private:
    Socket *skt;
    common_ftp *ftp;
    std::vector<common_proxy_client *> clients;
    bool exit = false;

public:
    common_acceptor(common_ftp *ftp, Socket *skt);

    virtual void run();

    void stop();

    ~common_acceptor();
};


#endif //CMAKE_DEMO_COMMON_ACCEPTOR_H
