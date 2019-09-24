//
// Created by mati on 19/9/19.
//

#ifndef CMAKE_DEMO_QUEUETOFILE_H
#define CMAKE_DEMO_QUEUETOFILE_H

#include "Thread.h"
#include "FileManager.h"
#include "BlockingQueue.h"
#include <vector>
#include <condition_variable>

class QueueToFile : public Thread {
private:
    FileManager *fileManager;
    std::vector<BlockingQueue *> queues;

public:
    explicit QueueToFile(FileManager *fileManager);

    virtual void run();

    void addQueue(BlockingQueue *bq);

    ~QueueToFile();
};

#endif //CMAKE_DEMO_QUEUETOFILE_H
