//
// Created by mati on 19/9/19.
//

#include "Compressor.h"
#include "FileManager.h"
#include <arpa/inet.h>
#include <bitset>

using namespace std;

Compressor::Compressor(unsigned int n, FileManager *fileManager, BlockingQueue *bq) {
    this->n = n;
    this->fileManager = fileManager;
    this->bq = bq;
}

void Compressor::startCompressor() {
    vector<unsigned int> block = this->fileManager->getBlock();

    if (block.size() < this->n)
        complete_block(&block, this->n);

    //calcula el minimo, maximo, bits necesarios y resta diferencia
    unsigned int min = get_min_element(&block);
    substract_min_to_block(&block, min);
    unsigned int max = get_max_element(&block);
    unsigned int number_of_digits = get_number_of_digits(max);

    //escribe el minimo y la cant de bits utilizados
    string s;
    s = std::bitset<sizeof(unsigned int) * 8>(min).to_string();
    s += std::bitset<sizeof(unsigned int) * 2>(number_of_digits).to_string();

    //comprime cada numero en bits.
    for (int i = 0; i < (int) block.size(); i++) {
        char buffer[MAX_DIGITS] = "";
        string s2 = std::bitset<MAX_DIGITS>(block.at(i)).to_string();
        s2.copy(buffer, number_of_digits, MAX_DIGITS - number_of_digits);
        s += buffer;
}

    //encola el bloque comprimido
    int resp = this->bq->pushData(s);
    while (resp == -1)
        resp = this->bq->pushData(s);

    block = this->fileManager->getBlock();
}

void Compressor::complete_block(vector<unsigned int> *block, unsigned int to) {
    for (unsigned int i = (int) block->size(); i < to; i++)
        block->push_back(block->back());
}

unsigned int Compressor::get_min_element(vector<unsigned int> *block) {
    unsigned int min = block->front();
    for (int i = 1; i < (int) block->size(); i++)
        if (min > block->at(i))
            min = block->at(i);

    return min;
}

unsigned int Compressor::get_max_element(vector<unsigned int> *block) {
    unsigned int max = block->front();
    for (int i = 1; i < (int) block->size(); i++)
        if (max < block->at(i))
            max = block->at(i);

    return max;
}

unsigned int Compressor::get_number_of_digits(unsigned int max) {
    unsigned int number_of_digits = 0;
    if (max == 0) return 0;

    do {
        ++number_of_digits;
        max /= 2;
    } while (max);

    return number_of_digits;
}

void Compressor::substract_min_to_block(vector<unsigned int> *block, unsigned int min) {
    for (int i = 0; i < (int) block->size(); i++)
        block->at(i) -= min;
}

Compressor::~Compressor() {}