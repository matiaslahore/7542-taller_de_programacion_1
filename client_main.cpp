#include "Client.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

int main(int argc, char *argv[]) {

    if (argc < 3){
        printf("faltan argumente");
        return 1;
    }

    Client client;
    client.run_client();

    return 0;
}
