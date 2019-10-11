//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_PROXY_CLIENT_H
#define CMAKE_DEMO_COMMON_PROXY_CLIENT_H

#define MKD_COMMAND "MKD"
#define PWD_COMMAND "PWD"
#define LIST_COMMAND "LIST"
#define RMD_COMMAND "RMD"
#define QUIT_COMMAND "QUIT"
#define LOGIN_USER_COMMAND "USER"
#define LOGIN_PSW_COMMAND "PASS"
#define MAX_RECV 500

#include "common_socket.h"
#include "common_ftp.h"
#include <atomic>
#include "Thread.h"

class common_proxy_client : public Thread {
private:
    Socket *skt;
    common_ftp *ftp;
    std::atomic<bool> exit;

public:
    common_proxy_client(common_ftp *ftp, Socket *skt);

    virtual void run();

    std::string receive();

    void send(const std::string &response);

    ~common_proxy_client();

    bool is_dead();

    void stop();
};


#endif //CMAKE_DEMO_COMMON_PROXY_CLIENT_H
