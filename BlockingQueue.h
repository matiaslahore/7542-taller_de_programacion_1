//
// Created by mati on 19/9/19.
//

#ifndef CMAKE_DEMO_BLOCKINGQUEUE_H
#define CMAKE_DEMO_BLOCKINGQUEUE_H


#include <string>
#include <queue>

using namespace std;


class BlockingQueue {
private:
    queue<string> s_queue;
    unsigned int q;
public:
    BlockingQueue(unsigned int q);

    int pushData(const string &s);

    string pullData();

    ~BlockingQueue();
};

#endif //CMAKE_DEMO_BLOCKINGQUEUE_H
