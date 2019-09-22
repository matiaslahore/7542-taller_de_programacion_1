//
// Created by mati on 19/9/19.
//

#include <queue>
#include "BlockingQueue.h"

using namespace std;

BlockingQueue::BlockingQueue(unsigned int q) {
    this->q = q;
}

int BlockingQueue::pushData(const string &s) {
    //if (this->s_queue.size() >= this->q)
    //    return -1;

    this->s_queue.push(s);
    
    return 0;
}

string BlockingQueue::pullData() {
    string to_return;

    if (!this->s_queue.empty()) {
        to_return = this->s_queue.front();
        this->s_queue.pop();
    }
    return to_return;
}

BlockingQueue::~BlockingQueue() {}