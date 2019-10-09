//
// Created by mati on 25/9/19.
//

#include <iostream>
#include <string>
#include "common_client.h"

common_client::common_client(char *host, char *port) {
    unsigned short port_i = atoi(port);
    this->proxyServer = new common_proxy_server(host, port_i);
}

void common_client::run_client() {
    std::string instruction;

    while (true) {
        std::getline(std::cin, instruction);
        this->proxyServer->send(instruction);
        this->proxyServer->receive();
        if (instruction == "QUIT") break;
    }
}

common_client::~common_client() = default;
