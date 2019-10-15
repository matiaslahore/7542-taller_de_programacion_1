//
// Created by mati on 25/9/19.
//

#include <string>
#include <iostream>
#include "common_server.h"
#include "common_acceptor.h"
#include "common_server_messages.h"

common_server::common_server(char *port, char *configPath) {
    int port_i = atoi(port);
    Socket socket(port_i);
    this->skt = std::move(socket);
    this->ftp = new common_ftp(configPath);
}

void common_server::run() {
    this->acceptor = new common_acceptor(this->ftp, this->skt);
    this->acceptor->start();
}

void common_server::stop() {
    this->acceptor->stop();
    this->skt.shutdown();
    this->acceptor->join();
}

common_server::~common_server() {
    delete this->ftp;
    delete this->acceptor;
}
