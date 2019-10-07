//
// Created by mati on 19/9/19.
//

#include <bitset>
#include <string>
#include <vector>
#include "Compressor.h"
#include "FileManager.h"

Compressor::Compressor(unsigned int n, FileManager *fileManager,
                       BlockingQueue *bq, unsigned int thread_id) {
    this->n = n;
    this->fileManager = fileManager;
    this->bq = bq;
    this->thread_id = thread_id;
}

void Compressor::run() {
    std::vector<uint32_t> block;
    block = this->fileManager->getBlock(this->thread_id);

    while (block.size() > 0) {
        if (block.size() < this->n)
            complete_block(&block, this->n);

        //calcula el minimo, maximo, bits necesarios y resta diferencia
        unsigned int min = get_min_element(&block);
        substract_min_to_block(&block, min);
        unsigned int max = get_max_element(&block);
        unsigned int number_of_digits = get_number_of_digits(max);

        //escribe el minimo y la cant de bits utilizados
        std::string s = std::bitset<sizeof(unsigned int) * 8>(min).to_string();

        s += std::bitset<sizeof(unsigned int) * 2>
                (number_of_digits).to_string();

        //comprime cada numero en bits.
        for (int i = 0; i < (int) block.size(); i++) {
            char buffer[MAX_DIGITS] = "";
            std::string s2 = std::bitset<MAX_DIGITS>(block.at(i)).to_string();
            s2.copy(buffer, number_of_digits, MAX_DIGITS - number_of_digits);
            s += buffer;
        }

        //completo a byte
        while ((s.length() % 8) != 0)
            s += "0";

        //encola el bloque comprimido
        this->bq->pushData(s);

        block = this->fileManager->getBlock(this->thread_id);
    }

    this->bq->freeQ();
}

void Compressor::complete_block(std::vector<unsigned int> *block,
                                unsigned int to) {
    for (unsigned int i = (int) block->size(); i < to; i++)
        block->push_back(block->back());
}

unsigned int Compressor::get_min_element(std::vector<unsigned int> *block) {
    unsigned int min = block->front();
    for (int i = 1; i < (int) block->size(); i++)
        if (min > block->at(i))
            min = block->at(i);

    return min;
}

unsigned int Compressor::get_max_element(std::vector<unsigned int> *block) {
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

void Compressor::substract_min_to_block(std::vector<unsigned int> *block,
                                        unsigned int min) {
    for (int i = 0; i < (int) block->size(); i++)
        block->at(i) -= min;
}

Compressor::~Compressor() {}
