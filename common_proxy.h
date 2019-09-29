//
// Created by mati on 27/9/19.
//

#ifndef CMAKE_DEMO_COMMON_PROXY_H
#define CMAKE_DEMO_COMMON_PROXY_H


#include "common_proxy_client.h"
#include <string>

class common_proxy {
private:
    common_proxy_client proxy_c;

public:
    common_proxy();

    std::string send(char *instruction);

    void recv(char *instruction);

    ~common_proxy();
};


#endif //CMAKE_DEMO_COMMON_PROXY_H
