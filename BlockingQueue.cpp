//
// Created by mati on 19/9/19.
//

#include <string>
#include "BlockingQueue.h"

BlockingQueue::BlockingQueue(unsigned int q) {
    this->q = q;
}

int BlockingQueue::pushData(const std::string &s) {
    if (this->s_queue.size() >= this->q)
        return -1;

    std::unique_lock<std::mutex> lock(this->m);
    this->s_queue.push(s);

    this->notified = true;
    this->cond_var.notify_all();

    return 0;
}

std::string BlockingQueue::pullData() {
    std::string to_return;
    std::unique_lock<std::mutex> lock(this->m);

    while (!this->notified) {  // loop to avoid spurious wakeups
        this->cond_var.wait_for(lock, std::chrono::milliseconds(50), [this] {
            return this->notified;
        }); //timeOut for end QueueToFile thread
        if (!this->s_queue.empty() && !this->notified) this->notified = true;
    }

    if (!this->s_queue.empty()) {
        to_return = this->s_queue.front();
        this->s_queue.pop();
    }

    this->notified = false;

    return to_return;
}

BlockingQueue::~BlockingQueue() {}
