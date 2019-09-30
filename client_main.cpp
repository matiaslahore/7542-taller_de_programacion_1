#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "common_client.h"

int main(int argc, char *argv[]) {

    if (argc < 3){
        printf("faltan argumente");
        return 1;
    }

    common_client client(argv[1], argv[2]);
    client.run_client();

    return 0;
}
