//
// Created by mati on 19/9/19.
//

#include "ThreadManager.h"
#include "FileManager.h"
#include "Compressor.h"
#include "BlockingQueue.h"
#include "QueueToFile.h"


ThreadManager::ThreadManager() {};

int ThreadManager::run_thread_manager(unsigned int n, unsigned int q,
                                      unsigned int t, const char *infile,
                                      const char *outfile) {
    FileManager fileM(n, t);
    if (fileM.startFileManager(infile, outfile) == -1) return -1;

    QueueToFile qtf = QueueToFile(&fileM);

    for (unsigned int i = 0; i < t; i++) {
        BlockingQueue bq = BlockingQueue();
        qtf.addQueue(&bq);
        Compressor comp = Compressor(n, q, &fileM, &bq);
        this->compressors.push_back(&comp);
    }

    //start only ONE compressor
    for (unsigned int i = 0; i < t; i++) {
        this->compressors.front()->startCompressor();
    }


    //Run compressor (threads)
    // joins threads
    return 0;
}

ThreadManager::~ThreadManager() {}