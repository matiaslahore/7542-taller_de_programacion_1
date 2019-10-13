//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_PROXY_CLIENT_H
#define CMAKE_DEMO_COMMON_PROXY_CLIENT_H

#define MAX_RECV 500

#include "common_socket.h"
#include "common_ftp.h"
#include <atomic>
#include "Thread.h"
#include "common_protocol.h"
#include "common_protocol.h"

class common_proxy_client : public Thread {
private:
    Socket *skt;
    common_ftp *ftp;
    std::atomic<bool> exit;
    common_protocol protocol;

public:
    common_proxy_client(common_ftp *ftp, Socket *skt);

    virtual void run();

    std::string receive();

    void send(const std::string &response);

    ~common_proxy_client();

    bool is_dead();

    void stop();

    int get_command_len(std::vector<char> &response);
};


#endif //CMAKE_DEMO_COMMON_PROXY_CLIENT_H
