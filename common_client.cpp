//
// Created by mati on 25/9/19.
//

#include <iostream>
#include "common_client.h"

common_client::common_client() = default;

void common_client::run_client() {
    bool exit = false;
    char str[80];

    while (!exit) {
        std::cin.getline(str, sizeof(str));

        try {
            this->proxyServer.send_instruction(str);
        } catch (...) {
            exit = true;
        }
    }
}

common_client::~common_client() = default;