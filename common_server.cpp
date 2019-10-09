//
// Created by mati on 25/9/19.
//

#include <string>
#include <iostream>
#include "common_server.h"
#include "common_server_messages.h"

common_server::common_server(char *port, char *configPath) {
    int port_i = atoi(port);
    this->skt = new Socket(port_i);
    //this->skt->bindAndListen(port_i);
    this->ftp = new common_ftp(configPath);
}

void common_server::run() {
    this->acceptor = new common_acceptor(this->ftp, this->skt);
    this->acceptor->start();
}

void common_server::stop(){
    this->acceptor->stop();
}

common_server::~common_server() {
    delete this->client;
}
