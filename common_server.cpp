//
// Created by mati on 25/9/19.
//

#include <string>
#include <iostream>
#include "common_server.h"
#include "common_server_messages.h"

common_server::common_server(char *port, char *configPath) {
    int port_i = atoi(port);
    this->client = new common_proxy_client(configPath, port_i);
}

void common_server::run_server() {
    bool exit = false;
    std::string instruction;

    while (!exit) {
        std::string response = this->client->receive();
        this->client->send(response);

        //std::getline(std::cin, instruction);
        //if (instruction == "q") exit = true;
    }
}

common_server::~common_server() {
    delete this->client;
}
