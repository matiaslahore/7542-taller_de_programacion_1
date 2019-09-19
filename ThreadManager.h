//
// Created by mati on 19/9/19.
//

#ifndef CMAKE_DEMO_THREADMANAGER_H
#define CMAKE_DEMO_THREADMANAGER_H

#include "Compressor.h"
#include <vector>

class ThreadManager {
private:
    std::vector<Compressor *> compressors;
public:
    ThreadManager();

    int run_thread_manager(unsigned int n, unsigned int q,
                           unsigned int t, const char *infile,
                           const char *outfile);

    ~ThreadManager();
};

#endif //CMAKE_DEMO_THREADMANAGER_H
