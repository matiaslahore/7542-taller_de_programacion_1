//
// Created by mati on 23/9/19.
//

#ifndef CMAKE_DEMO_THREAD_CPP
#define CMAKE_DEMO_THREAD_CPP

#include <thread>

class Thread {
private:
    std::thread thread;

public:
    Thread() {}

    void start() {
        thread = std::thread(&Thread::run, this);
    }

    void join() {
        thread.join();
    }

    virtual void run() = 0;

    virtual ~Thread() {}
};

#endif //CMAKE_DEMO_THREAD_CPP
