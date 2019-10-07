//
// Created by mati on 19/9/19.
//

#include <string>
#include "BlockingQueue.h"

BlockingQueue::BlockingQueue(unsigned int q) {
    this->q = q;
}

int BlockingQueue::pushData(const std::string &s) {
    std::unique_lock<std::mutex> lock(this->m);

    while (this->s_queue.size() >= this->q)
        this->cond_var_push.wait(lock);

    this->s_queue.push(s);
    this->cond_var_pull.notify_all();

    return 0;
}

std::string BlockingQueue::pullData() {
    std::unique_lock<std::mutex> lock(this->m);

    while (this->s_queue.empty())
        this->cond_var_pull.wait(lock);

    std::string to_return = this->s_queue.front();
    this->s_queue.pop();
    this->cond_var_push.notify_all();

    return to_return;
}

void BlockingQueue::freeQ() {
    this->pushData("");
}

BlockingQueue::~BlockingQueue() = default;
