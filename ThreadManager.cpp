//
// Created by mati on 19/9/19.
//

#include <mutex>
#include "FileManager.h"
#include "Compressor.h"
#include "BlockingQueue.h"
#include "QueueToFile.h"
#include "Thread.h"
#include "ThreadManager.h"


ThreadManager::ThreadManager() {}

int ThreadManager::run_thread_manager(unsigned int n, unsigned int q,
                                      unsigned int t, const char *infile,
                                      const char *outfile) {
    vector<Thread *> threads;
    mutex m;

    FileManager *fileM = new FileManager(n, t, n, m);
    if (fileM->startFileManager(infile, outfile) == 1) return -1;

    QueueToFile *qtf = new QueueToFile(fileM);

    for (unsigned int i = 0; i < t; i++) {
        BlockingQueue *bq = new BlockingQueue(q);
        qtf->addQueue(bq);
        Compressor *comp = new Compressor(n, fileM, bq, i);
        threads.push_back(comp);
    }

    threads.push_back(qtf);

    //Run threads
    for (unsigned int i = 0; i <= t; i++) {
        threads[i]->start();
    }

    //join and deletes
    for (unsigned int i = 0; i <= t; i++) {
        threads[i]->join();
        delete threads[i];
    }
    delete fileM;

    return 0;
}

ThreadManager::~ThreadManager() {}