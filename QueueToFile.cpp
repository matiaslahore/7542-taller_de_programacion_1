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

    return 0;
}


void QueueToFile::addQueue(BlockingQueue *bq) {
    queues.push_back(bq);
}


QueueToFile::~QueueToFile() {}