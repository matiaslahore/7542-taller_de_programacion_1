//
// Created by mati on 27/9/19.
//

#include "Proxy.h"


Proxy::Proxy() {

}

std::string Proxy::send(char *instruction) {
    //Recive y se comunica en teoria por socket
    //pero ahora se comunica a un proxy server

    return this->proxy_c.send_command(instruction);
}

void Proxy::recv(char *instruction) {

}

Proxy::~Proxy() {}