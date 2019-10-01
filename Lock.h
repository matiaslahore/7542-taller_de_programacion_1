//
// Created by mati on 1/10/19.
//

#ifndef CMAKE_DEMO_LOCK_H
#define CMAKE_DEMO_LOCK_H

#endif //CMAKE_DEMO_LOCK_H

class Lock {
private:
    std::mutex &m;

public:
    Lock(std::mutex &m) : m(m) {
        m.lock();
    }

    ~Lock() {
        m.unlock();
    }

private:
    Lock(const Lock &) = delete;

    Lock &operator=(const Lock &) = delete;

    Lock(Lock &&) = delete;

    Lock &operator=(Lock &&) = delete;

};
