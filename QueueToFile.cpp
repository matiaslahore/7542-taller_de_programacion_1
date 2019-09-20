//
// Created by mati on 19/9/19.
//

#include "QueueToFile.h"
#include "FileManager.h"
#include "BlockingQueue.h"


using namespace std;

QueueToFile::QueueToFile(FileManager *fileManager) {
    this->fileManager = fileManager;
};

int QueueToFile::startQueueToFile() {

    string buff;
    for (int i = 0; i < this->queues.size(); i++) {
        buff += this->queues.at(i)->pullData();
    }

    this->fileManager->saveStream(buff);
    return 0;
}

void QueueToFile::addQueue(BlockingQueue *bq) {
    queues.push_back(bq);
}

QueueToFile::~QueueToFile() {}