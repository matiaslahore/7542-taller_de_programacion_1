//
// Created by mati on 19/9/19.
//

#ifndef CMAKE_DEMO_BLOCKINGQUEUE_H
#define CMAKE_DEMO_BLOCKINGQUEUE_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

class BlockingQueue {
private:
    std::queue<std::string> s_queue;
    unsigned int q;
    std::mutex m;
    std::condition_variable cond_var_pull;
    std::condition_variable cond_var_push;

public:
    explicit BlockingQueue(unsigned int q);

    int pushData(const std::string &s);

    std::string pullData();

    void freeQ();
};

#endif //CMAKE_DEMO_BLOCKINGQUEUE_H
