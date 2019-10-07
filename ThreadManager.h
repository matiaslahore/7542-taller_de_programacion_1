//
// Created by mati on 19/9/19.
//

#ifndef CMAKE_DEMO_THREADMANAGER_H
#define CMAKE_DEMO_THREADMANAGER_H

class ThreadManager {
private:
public:
    int run_thread_manager(unsigned int n, unsigned int q,
                           unsigned int t, const char *infile,
                           const char *outfile);
};

#endif //CMAKE_DEMO_THREADMANAGER_H
