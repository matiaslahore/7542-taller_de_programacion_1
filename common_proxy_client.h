//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_PROXY_CLIENT_H
#define CMAKE_DEMO_COMMON_PROXY_CLIENT_H


#include "common_socket.h"
#include "common_ftp.h"
#include "Thread.h"
#include <string>

class common_proxy_client : public Thread {
private:
    Socket &skt;
    common_ftp &ftp;
    bool exit = false;

public:
    common_proxy_client(common_ftp &ftp, Socket &skt);

    virtual void run();

    std::string receive();

    void send(const std::string& response);

    ~common_proxy_client();

    bool is_dead();

    void stop();
};


#endif //CMAKE_DEMO_COMMON_PROXY_CLIENT_H
