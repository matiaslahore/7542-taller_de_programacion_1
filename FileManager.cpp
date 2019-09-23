//
// Created by mati on 19/9/19.
//

#include <fstream>
#include <cstdlib>
#include <arpa/inet.h>
#include <vector>
#include <bitset>
#include "FileManager.h"

using namespace std;

FileManager::FileManager(unsigned int n, unsigned int seeks) {
    this->n = n;
    this->seeks = seeks;
}

int FileManager::startFileManager(const char *infile, const char *outfile) {
    this->fin.open(infile, std::ifstream::in | std::ifstream::binary);
    this->fout.open(outfile, std::ifstream::out | std::ifstream::binary);
    if ((!fin.is_open()) || (!fout.is_open())) return EXIT_FAILURE;

    return 0;
}

vector<unsigned int> FileManager::getBlock() {
    vector<unsigned int> block;
    unsigned int i = 0;
    uint32_t a;

    //obtiene los numeros del archivo y los carga en block
    for (; (i < this->n) && this->fin; i++) {
        this->fin.read(reinterpret_cast<char *>(&a), 4);
        block.push_back(ntohl((a)));
    }

    if (i == 1) block.empty();

    printf("block:%i.\n", block.size());
    for (int x = 0; x < block.size(); x++)
        printf("x: %i ; value:%i.\n", x, block.at(x));

    return block;
}

void FileManager::saveStream(string s) {
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