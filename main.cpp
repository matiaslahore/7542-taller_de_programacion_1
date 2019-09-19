#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "ThreadManager.h"

using namespace std;


int main(int argc, char *argv[]) {

    unsigned int n = strtol(argv[1], NULL, 10);
    unsigned int q = strtol(argv[2], NULL, 10);
    unsigned int t = strtol(argv[3], NULL, 10);
    const char *infile = argv[4], *outfile = argv[5];
    ThreadManager thm;

    thm.run_thread_manager(n, q, t, infile, outfile);
    return 0;
}
