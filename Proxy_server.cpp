//
// Created by mati on 25/9/19.
//

#include <string>
#include <cstring>
#include "Proxy_server.h"

#define QUIT_COMMAND "QUIT"


Proxy_server::Proxy_server() {}

void Proxy_server::send_instruction(char *instruction) {
    std::string resp = this->proxy.send(instruction);
    printf("%s\n", resp.c_str());

    if (strncmp(instruction, QUIT_COMMAND, 4) == 0)
        throw "QUIT";

}

Proxy_server::~Proxy_server() {}