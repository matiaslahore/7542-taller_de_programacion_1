//
// Created by mati on 25/9/19.
//

#include <iostream>
#include "common_client.h"

common_client::common_client() = default;

void common_client::run_client() {
    bool exit = false;
    std::string instruction;

    while (!exit) {
        //std::cin.getline(str, sizeof(str));
        std::getline(std::cin, instruction);
        try {
            this->proxyServer.send(instruction);
            this->proxyServer.receive();

        } catch (...) {
            exit = true;
        }
    }
}

common_client::~common_client() = default;