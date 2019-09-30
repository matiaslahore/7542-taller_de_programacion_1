//
// Created by mati on 25/9/19.
//

#include <string>
#include <cstring>
#include "common_proxy_server.h"

#define QUIT_COMMAND "QUIT"

common_proxy_server::common_proxy_server() = default;

void common_proxy_server::send_instruction(char *instruction) {
    std::string resp = "this->commonProxy.send(instruction)";
    printf("%s\n", resp.c_str());

    if (strncmp(instruction, QUIT_COMMAND, 4) == 0)
        throw "QUIT";

}

common_proxy_server::~common_proxy_server() = default;