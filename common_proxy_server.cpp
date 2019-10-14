//
// Created by mati on 25/9/19.
//

#include <string>
#include <cstring>
#include <vector>
#include "common_proxy_server.h"

#define QUIT_COMMAND "QUIT"

common_proxy_server::common_proxy_server(char *host, int port) {
    this->skt.connect(host, port);
}

void common_proxy_server::send(std::string &instruction) {
    instruction += "\n";
    const char *cstr = instruction.c_str();

    this->skt.send(cstr, strlen(cstr));
}

void common_proxy_server::receive() {
    std::vector<char> response;
    response.resize(MAX_RECV);
    this->skt.receive(response.data(), MAX_RECV);
    printf("%s\n", response.data());
}

common_proxy_server::~common_proxy_server() = default;
