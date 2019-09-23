//
// Created by mati on 19/9/19.
//

#include "QueueToFile.h"
#include "FileManager.h"
#include "BlockingQueue.h"


using namespace std;

QueueToFile::QueueToFile(FileManager *fileManager) {
    this->fileManager = fileManager;
}

void QueueToFile::run() {

    string buff = " ";
    //Round Robin
    while (buff.length() > 0) {
        for (int i = 0; i < (int) this->queues.size(); i++) {
            buff = this->queues.at(i)->pullData();
            if (buff.length() > 0)
                this->fileManager->saveStream(buff);
        }
    }

    printf("llegue 2\n");

}

void QueueToFile::addQueue(BlockingQueue *bq) {
    queues.push_back(bq);
}

QueueToFile::~QueueToFile() {
    for (int i = 0; i < (int) this->queues.size(); i++)
        delete this->queues.at(i);
}