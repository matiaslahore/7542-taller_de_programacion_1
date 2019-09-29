//
// Created by mati on 27/9/19.
//

#include "common_proxy.h"


common_proxy::common_proxy() {

}

std::string common_proxy::send(char *instruction) {
    //Recive y se comunica en teoria por socket
    //pero ahora se comunica a un proxy server

    return this->proxy_c.send_command(instruction);
}

void common_proxy::recv(char *instruction) {

}

common_proxy::~common_proxy() {}