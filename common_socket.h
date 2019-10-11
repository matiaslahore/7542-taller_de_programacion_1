//
// Created by mati on 29/9/19.
//

#ifndef CMAKE_DEMO_COMMON_SOCKET_H
#define CMAKE_DEMO_COMMON_SOCKET_H

#include "cstddef"

#define CONNECTION_SUCCESS 1
#define CONNECTION_FAIL -1
#define MAX_CLIENT 5

class Socket {
private:
    int skt;

public:
    Socket();

    int bindAndListen(unsigned short port);

    int connect(const char *host_name, unsigned short port);

    Socket accept();

    int receive(char *buffer, std::size_t length);

    int send(const char *buffer, std::size_t length);

    void shutdown();

    bool invalid();

    ~Socket();

    Socket(Socket &&other);

    Socket &operator=(Socket &&other);
};


#endif //CMAKE_DEMO_COMMON_SOCKET_H
