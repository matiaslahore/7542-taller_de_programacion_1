//
// Created by mati on 19/9/19.
//

#ifndef CMAKE_DEMO_COMPRESSOR_H
#define CMAKE_DEMO_COMPRESSOR_H

#include "FileManager.h"
#include "BlockingQueue.h"

#define MIN_BITS_TO_SAVE 8

class Compressor {
private:
    unsigned int n;
    FileManager *fileManager;
    BlockingQueue *bq;

    static void complete_block(vector<unsigned int> *block, unsigned int to);

    static void substract_min_to_block(vector<unsigned int> *block, unsigned int min);

    static unsigned int get_number_of_digits(unsigned int max);

    static unsigned int get_max_element(vector<unsigned int> *block);

    static unsigned int get_min_element(vector<unsigned int> *block);

public:

    Compressor(unsigned int n, FileManager *fileManager, BlockingQueue *bq);

    void startCompressor();

    ~Compressor();
};


#endif //CMAKE_DEMO_COMPRESSOR_H
