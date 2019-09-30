//
// Created by mati on 25/9/19.
//

#include <string>
#include <cstring>
#include "common_proxy_server.h"

#define QUIT_COMMAND "QUIT"

common_proxy_server::common_proxy_server() {
    this->skt.connect("127.0.0.1", 1050);
}

void common_proxy_server::send(std::string instruction) {
    instruction += "\n";
    const char *cstr = instruction.c_str();

    this->skt.send(cstr, strlen(cstr));

    if (strncmp(cstr, QUIT_COMMAND, 4) == 0)
        throw std::exception();
}

void common_proxy_server::receive() {
    char response[500] = "";
    this->skt.receive(response, sizeof(response));
    printf("%s\n", response);
}

common_proxy_server::~common_proxy_server() = default;