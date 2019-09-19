//
// Created by mati on 19/9/19.
//

#ifndef CMAKE_DEMO_QUEUETOFILE_H
#define CMAKE_DEMO_QUEUETOFILE_H

#include "FileManager.h"
#include "BlockingQueue.h"
#include <vector>

class QueueToFile {
private:
    FileManager *fileManager;
    std::vector<BlockingQueue *> queues;
public:
    QueueToFile(FileManager *fileManager);

    int startQueueToFile();

    void addQueue(BlockingQueue *bq);

    ~QueueToFile();
};

#endif //CMAKE_DEMO_QUEUETOFILE_H
