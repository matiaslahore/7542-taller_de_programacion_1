//
// Created by mati on 27/9/19.
//

#ifndef CMAKE_DEMO_PROXY_H
#define CMAKE_DEMO_PROXY_H


#include "Proxy_client.h"
#include <string>

class Proxy {
private:
    Proxy_client proxy_c;

public:
    Proxy();

    std::string send(char *instruction);

    void recv(char *instruction);

    ~Proxy();
};


#endif //CMAKE_DEMO_PROXY_H
