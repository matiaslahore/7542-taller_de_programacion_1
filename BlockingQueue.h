//
// Created by mati on 19/9/19.
//

#ifndef CMAKE_DEMO_BLOCKINGQUEUE_H
#define CMAKE_DEMO_BLOCKINGQUEUE_H


#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;


class BlockingQueue {
private:
    queue<string> s_queue;
    unsigned int q;
    mutex m;
    condition_variable cond_var;
    bool notified;
public:
    BlockingQueue(unsigned int q);

    int pushData(const string &s);

    string pullData();

    ~BlockingQueue();
};

#endif //CMAKE_DEMO_BLOCKINGQUEUE_H
