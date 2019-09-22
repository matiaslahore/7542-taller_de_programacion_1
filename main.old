#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <bitset>
#include <cstring>

#define MAX_DIGITS 12
#define MAX_BLOCKS 8
#define MIN_BITS_TO_SAVE 8


using namespace std;

void print_vector(unsigned int *block, unsigned short int len) {
    for (int i = 0; i < len; i++)
        printf("pos %i :%x.\n", i, block[i]);

    printf("\n");
}

unsigned int get_min_element(const unsigned int *block,
                             unsigned short int len) {
    unsigned int min = block[0];
    for (int i = 1; i < len; i++)
        if (min > block[i])
            min = block[i];

    return min;
}

unsigned int get_max_element(const unsigned int *block,
                             unsigned short int len) {
    unsigned int max = block[0];
    for (int i = 1; i < len; i++)
        if (max < block[i])
            max = block[i];

    return max;
}

unsigned int get_number_of_digits(unsigned int max) {
    unsigned int number_of_digits = 0;
    if (max == 0) return 0;

    do {
        ++number_of_digits;
        max /= 2;
    } while (max);

    return number_of_digits;
}

void substract_min_to_block(unsigned int *block, unsigned int min,
                            unsigned short int len) {
    for (int i = 0; i < len; i++)
        block[i] -= min;
}

void complete_block(unsigned int *block, unsigned int from,
                    unsigned short int to) {
    unsigned int number = block[from - 1];
    for (unsigned int i = from; i < to; i++)
        block[i] = number;
}

bool is_valid_parameters(int argc, char **argv) {
    return true;
}

int main(int argc, char *argv[]) {
    if (!is_valid_parameters(argc, argv)) return 1;
    unsigned short int numbers_per_block = strtol(argv[1], NULL, 10);
    const char *input_file = argv[4];
    const char *output_file = argv[5];

    fstream fin;
    fin.open(input_file, std::ifstream::in | std::ifstream::binary);
    fstream fout;
    fout.open(output_file, std::ifstream::out | std::ifstream::binary);
    if ((!fin.is_open()) || (!fout.is_open())) return EXIT_FAILURE;

    while (fin) {
        unsigned int block[MAX_BLOCKS] = {0};
        unsigned int i = 0;

        //obtiene los numeros del archivo y los carga en block
        char *bufferx = new char[4];
        for (; (i < numbers_per_block) && fin; i++) {
            fin.read(bufferx, 4);
            block[i] = ntohl(*(int *) (bufferx));
        }

        delete[] bufferx;
        if (i == 1) break;


        if (i < numbers_per_block)
            complete_block(block, i - 1, numbers_per_block);

        //calcula el minimo, maximo, bits necesarios y resta diferencia
        unsigned int min = get_min_element(block, numbers_per_block);
        substract_min_to_block(block, min, numbers_per_block);
        unsigned int max = get_max_element(block, numbers_per_block);
        unsigned int number_of_digits = get_number_of_digits(max);

        //escribe el minimo y la cant de bits utilizados
        int min_big = htonl(min);
        fout.write((char *) &min_big, sizeof(min_big));
        std::bitset<MIN_BITS_TO_SAVE> numb_dig_bits(number_of_digits);
        fout.write((char *) &numb_dig_bits, 1);


        //convierte la dif de numeros en bits
        string s;
        for (int q = 0; q < numbers_per_block; q++) {
            char buffer[MAX_DIGITS] = "";
            string s2 = std::bitset<MAX_DIGITS>(block[q]).to_string();
            s2.copy(buffer, number_of_digits, MAX_DIGITS - number_of_digits);
            s += buffer;
            while ((s.length() >= MIN_BITS_TO_SAVE) ||
                   ((s.length() > 0) && (q == numbers_per_block - 1))) {
                std::bitset<MIN_BITS_TO_SAVE> outNum(s);
                fout.write((char *) &outNum, 1);
                s.erase(0, MIN_BITS_TO_SAVE);
            }
        }
    }

    fin.close();
    fout.close();
    return 0;
}
