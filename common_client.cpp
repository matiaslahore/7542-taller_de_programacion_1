//
// Created by mati on 25/9/19.
//

#include <string>
#include <iostream>
#include "common_client.h"

/** Constructor
 *  @param host of server
 *  @param port of server
 */
common_client::common_client(char *host, char *port) {
    int port_i = atoi(port);
    this->proxyServer = new common_proxy_server(host, port_i);
}

void common_client::run_client() {
    this->proxyServer->receive();
    std::string instruction;
    bool exit = false;

    while (!exit) {
        std::getline(std::cin, instruction);
        if (instruction == "QUIT") exit = true;
        if (std::cin.eof()) exit = true;
        if (instruction.length() < 3) continue;
        this->proxyServer->send(instruction);
        this->proxyServer->receive();
    }
}

common_client::~common_client() {
    delete this->proxyServer;
}
