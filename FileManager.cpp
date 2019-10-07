//
// Created by mati on 19/9/19.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <arpa/inet.h>
#include <vector>
#include <bitset>
#include <string>
#include <mutex>
#include <cstring>
#include "FileManager.h"

FileManager::FileManager(unsigned int n, unsigned int quantity_threads,
                         unsigned int num_per_block, std::mutex &m) : m(m) {
    this->n = n;
    unsigned int q = 0;
    this->seek = quantity_threads;

    for (unsigned int i = 0; i < quantity_threads; ++i) {
        this->pos_threads.push_back(q);
        q += (NUMBER_LENGHT * num_per_block);
    }
}

int FileManager::startFileManager(const char *infile, const char *outfile) {
    this->fin.open(infile, std::ifstream::in | std::ifstream::binary);
    this->fout.open(outfile, std::ifstream::out | std::ifstream::binary);

    //change file to stdin or stdout
    if (strncmp(outfile, "-", 1) == 0)
        this->fout.basic_ios<char>::rdbuf(std::cout.rdbuf());
    if (strncmp(infile, "-", 1) == 0)
        this->fin.basic_ios<char>::rdbuf(std::cin.rdbuf());

    if ((!fin.is_open()) || (!fout.is_open())) return EXIT_FAILURE;

    this->fin.seekg(0, this->fin.end);
    this->length = this->fin.tellg();
    this->fin.seekg(0, this->fin.beg);

    return 0;
}

std::vector<uint32_t> FileManager::getBlock(unsigned int thread_id) {
    uint32_t *block = new uint32_t[this->n];
    std::vector<uint32_t> block_v;

    if (this->pos_threads[thread_id] < this->length) {
        unsigned int to_read = NUMBER_LENGHT * this->n;
        if ((this->pos_threads[thread_id] + to_read) > this->length)
            to_read = this->length - this->pos_threads[thread_id];

        this->m.lock();
        this->fin.seekg(this->pos_threads[thread_id], std::ifstream::beg);
        this->fin.read((char *) block, to_read);
        this->m.unlock();

        for (unsigned int i = 0; i < (to_read / NUMBER_LENGHT); i++)
            block_v.push_back(ntohl((block[i])));

        this->pos_threads[thread_id] += to_read * this->seek;
    }

    free(block);

    return block_v;
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
