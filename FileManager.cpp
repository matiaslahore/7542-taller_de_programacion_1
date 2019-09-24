//
// Created by mati on 19/9/19.
//

#include <fstream>
#include <cstdlib>
#include <arpa/inet.h>
#include <vector>
#include <bitset>
#include <string>
#include <mutex>
#include "FileManager.h"

FileManager::FileManager(unsigned int n, unsigned int quantity_threads,
                         unsigned int num_per_block, std::mutex &m) : m(m) {
    this->n = n;
    unsigned int q = 0;
    this->seek = (NUMBER_LENGHT * num_per_block * quantity_threads);

    for (unsigned int i = 0; i < quantity_threads; ++i) {
        this->pos_threads.push_back(q);
        q += (NUMBER_LENGHT * num_per_block);
    }
}

int FileManager::startFileManager(const char *infile, const char *outfile) {
    this->fin.open(infile, std::ifstream::in | std::ifstream::binary);
    this->fout.open(outfile, std::ifstream::out | std::ifstream::binary);
    if ((!fin.is_open()) || (!fout.is_open())) return EXIT_FAILURE;

    return 0;
}

std::vector<unsigned int> FileManager::getBlock(unsigned int thread_id) {
    std::vector<unsigned int> block;
    unsigned int i = 0;
    uint32_t a;

    this->m.lock();
    this->fin.seekg(this->pos_threads[thread_id], std::ifstream::beg);
    //printf("1- hilo:%i, en la pos:%i.\n", thread_id, (int) this->fin.tellg());

    //obtiene los numeros del archivo y los carga en block
    for (; (i < this->n) && this->fin; i++) {
        this->fin.read(reinterpret_cast<char *>(&a), NUMBER_LENGHT);
        block.push_back(ntohl((a)));
    }

    this->pos_threads[thread_id] += this->seek;
    this->m.unlock();

    if (i == 1) block.clear();
/*
    printf("block:%i.\n", (int) block.size());
    for (int x = 0; x < (int) block.size(); x++)
        printf("x: %i ; value:%X.\n", x, block.at(x));
*/
    return block;
}

void FileManager::saveStream(std::string s) {
    this->buffer_s += s;

    while (this->buffer_s.length() >= MIN_BITS_TO_SAVE) {
        std::bitset<MIN_BITS_TO_SAVE> outNum(this->buffer_s);
        this->fout.write((char *) &outNum, 1);
        this->buffer_s.erase(0, MIN_BITS_TO_SAVE);
    }
}

FileManager::~FileManager() {
    this->fin.close();
    this->fout.close();
}
