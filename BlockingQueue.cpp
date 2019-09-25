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

    //cambiar esto por otra condition variable
    if (this->s_queue.size() >= this->q)
        return -1;

    this->s_queue.push(s);
    this->cond_var.notify_all();

    return 0;
}

std::string BlockingQueue::pullData() {
    std::string to_return = " ";
    std::unique_lock<std::mutex> lock(this->m);

    while (this->s_queue.empty()) {  // loop to avoid spurious wakeups
        this->cond_var.wait(lock);
    }

    if (!this->s_queue.empty()) {
        to_return = this->s_queue.front();
        this->s_queue.pop();
    }

    return to_return;
}

void BlockingQueue::freeQ() {
    while (this->pushData("") == -1) {} //send end of data to queue
}

BlockingQueue::~BlockingQueue() = default;
