//
// Created by mati on 29/9/19.
//

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <syslog.h>
#include <cerrno>
#include <exception>
#include <algorithm>
#include "common_socket.h"

Socket::Socket() {
    this->skt = socket(AF_INET, SOCK_STREAM, 0);
    if (this->skt == -1) throw -1;

    int value = 1;
    int sAux = this->skt;
    int s = setsockopt(sAux, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

    if (s == CONNECTION_FAIL) ::shutdown(this->skt, SHUT_RDWR);
}

int Socket::bindAndListen(unsigned short port) {
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(serv_addr.sin_zero), sizeof(serv_addr.sin_zero));

    if (bind(this->skt, (struct sockaddr *) &serv_addr,
             (socklen_t)
                     sizeof(struct sockaddr)) == CONNECTION_FAIL)
        return CONNECTION_FAIL;

    if (listen(this->skt, MAX_CLIENT) == -1)
        return CONNECTION_FAIL;

    return CONNECTION_SUCCESS;
}

int Socket::connect(const char *host_name, unsigned short port) {
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(host_name);
    bzero(address.sin_zero, sizeof(address.sin_zero));

    if (::connect(this->skt, (struct sockaddr *) &address,
                  (socklen_t)
                          sizeof(struct sockaddr)) == -1)
        return CONNECTION_FAIL;

    return CONNECTION_SUCCESS;
}

Socket Socket::accept() {
    Socket accepted;
    accepted.skt = ::accept(this->skt, nullptr, nullptr);
    if (accepted.invalid())
        throw std::exception();

    return accepted;
}

int Socket::send(const char *buffer, size_t length) {
    size_t sent = 0;
    int s = 0;
    bool is_the_socket_valid = true;

    while (sent < length && is_the_socket_valid) {
        s = ::send(this->skt, &buffer[sent], length - sent, MSG_NOSIGNAL);

        if (s == 0)
            is_the_socket_valid = false;
        else if (s < 0)
            is_the_socket_valid = false;
        else
            sent += s;
    }

    if (is_the_socket_valid) {
        return sent;
    } else {
        return CONNECTION_FAIL;
    }
}

int Socket::receive(char *buffer, size_t length) {
    size_t received = 0;
    int s = 0;
    bool is_the_socket_valid = true;

    while (received < length && is_the_socket_valid) {
        s = ::recv(this->skt, &buffer[received], length - received,
                   MSG_NOSIGNAL);

        if (s == 0)
            is_the_socket_valid = false;
        else if (s < 0)
            is_the_socket_valid = false;
        else
            received += s;

        if ((is_the_socket_valid) &&
            (strncmp(&buffer[received - 1], "\n", 1) == 0))
            is_the_socket_valid = false;
    }

    if (received > 0)
        buffer[received - 1] = '\0';

    if (is_the_socket_valid || received)
        return received;

    return CONNECTION_FAIL;
}

void Socket::shutdown() {
    this->skt = ::shutdown(this->skt, SHUT_RDWR);
    close(this->skt);
}

bool Socket::invalid() {
    return (this->skt <= 0);
}

Socket::~Socket() {
    if (this->skt >= 0)
        close(this->skt);
}

Socket::Socket(Socket &&other) {
    this->skt = std::move(other.skt);
    other.skt = -1;
}

Socket &Socket::operator=(Socket &&other) {
    this->skt = std::move(other.skt);
    other.skt = -1;
    return *this;
}
