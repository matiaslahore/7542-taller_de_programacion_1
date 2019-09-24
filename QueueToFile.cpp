//
// Created by mati on 19/9/19.
//

#include <iostream>
#include <string>
#include <vector>
#include "QueueToFile.h"
#include "FileManager.h"
#include "BlockingQueue.h"

QueueToFile::QueueToFile(FileManager *fileManager) {
    this->fileManager = fileManager;
}

void QueueToFile::run() {
    bool runing = true;
    std::string buff = "";
    std::vector<bool> buffer_states((int) this->queues.size(), true);

    //Round Robin
    while (runing) {
        for (int i = 0; (i < (int) this->queues.size()); i++) {
            buff = this->queues.at(i)->pullData();
            if (buff.length() > 0) {
                this->fileManager->saveStream(buff);
            } else {
                buffer_states[i] = false;
                runing = false;
                for (int j = 0; j < (int) buffer_states.size(); j++) {
                    if (buffer_states[j])
                        runing = true;
                }
            }
        }
    }
}

void QueueToFile::addQueue(BlockingQueue *bq) {
    queues.push_back(bq);
}

QueueToFile::~QueueToFile() {
    for (int i = 0; i < (int) this->queues.size(); i++)
        delete this->queues.at(i);
}
