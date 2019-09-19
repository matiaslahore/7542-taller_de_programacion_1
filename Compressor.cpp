//
// Created by mati on 19/9/19.
//

#include "Compressor.h"
#include "FileManager.h"
#include <arpa/inet.h>
#include <bitset>

using namespace std;

Compressor::Compressor(unsigned int n, unsigned int q, FileManager *fileManager, BlockingQueue *bq) {
    this->n = n;
    this->q = q;
    this->fileManager = fileManager;
    this->bq = bq;
};


int Compressor::startCompressor() {
    vector<unsigned int> block = this->fileManager->getBlock();

    if (block.size() < this->n)
        complete_block(&block, this->n);



    //calcula el minimo, maximo, bits necesarios y resta diferencia
    unsigned int min = get_min_element(&block);
    substract_min_to_block(&block, min);
    unsigned int max = get_max_element(&block);
    unsigned int number_of_digits = get_number_of_digits(max);


    for (int i = 0; i < block.size(); i++) {
        printf("elem:%x.\n", block[i]);
    }

    //escribe el minimo y la cant de bits utilizados
    int min_big = htonl(min);
    string s2 = std::bitset<MAX_DIGITS * 8>(min_big).to_string();
    //this->bq->

    /*
    fout.write((char *) &min_big, sizeof(min_big));
    bitset<MIN_BITS_TO_SAVE> numb_dig_bits(number_of_digits);
    fout.write((char *) &numb_dig_bits, 1);

    char buffer[MAX_DIGITS] = "";
    string s2 = std::bitset<MAX_DIGITS>(block[q]).to_string();
    s2.copy(buffer, number_of_digits, MAX_DIGITS - number_of_digits);
    s += buffer;
*/

    return 0;
}

void Compressor::complete_block(vector<unsigned int> *block, unsigned int to) {
    for (unsigned int i = block->size(); i < to; i++)
        block->push_back(block->back());
}

unsigned int Compressor::get_min_element(vector<unsigned int> *block) {
    unsigned int min = block->front();
    for (int i = 1; i < block->size(); i++)
        if (min > block->at(i))
            min = block->at(i);

    return min;
}

unsigned int Compressor::get_max_element(vector<unsigned int> *block) {
    unsigned int max = block->front();
    for (int i = 1; i < block->size(); i++)
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
    for (int i = 0; i < block->size(); i++)
        block->at(i) -= min;
}

Compressor::~Compressor() {}