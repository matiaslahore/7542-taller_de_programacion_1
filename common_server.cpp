//
// Created by mati on 25/9/19.
//

#include <string>
#include <iostream>
#include "common_server.h"
#include "common_server_messages.h"

common_server::common_server() {
    char configPath[20] = "config.cfg";
    this->client = new common_proxy_client(configPath);
}

void common_server::run_server() {
    bool exit = false;
    std::string instruction;

    while (!exit) {
        std::string response = this->client->recive();
        this->client->send(response);

        //std::getline(std::cin, instruction);
        //if (instruction == "q") exit = true;
    }
}

common_server::~common_server() {
    delete this->client;
}
