//
// Created by mati on 25/9/19.
//


#include <string>
#include <iostream>
#include "Client.h"
#include "Proxy_server.h"


Client::Client() {}

void Client::run_client() {
    bool exit = false;
    char str[80];
    Proxy_server proxyServer;

    while (!exit) {
        std::cin.getline(str, sizeof(str));

        try {
            proxyServer.send_instruction(str);
        } catch (...) {
            exit = true;
        }
    }
}

Client::~Client() {}