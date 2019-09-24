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
    bool running = true;
    std::string buff = "";
    std::vector<bool> buffer_states((int) this->queues.size(), true);

    //Round Robin
    while (running) {
        for (int i = 0; (i < (int) this->queues.size()); i++) {
            if (!buffer_states[i]) continue; //continue if queue already done
            buff = this->queues.at(i)->pullData();
            if (buff.length() > 0) {
                this->fileManager->saveStream(buff);
            } else {
                buffer_states[i] = false;
                running = false;
                for (int j = 0; j < (int) buffer_states.size(); j++) {
                    if (buffer_states.at(j))
                        running = true;
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
