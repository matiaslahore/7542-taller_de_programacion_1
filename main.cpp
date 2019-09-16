#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <string>
//#include <iostream>
#include <bitset>
#include <cstring>

using namespace std;

void print_vector(unsigned int *block, unsigned short int len) {
    for (int i = 0; i < len; i++)
        printf("pos %i :%x.\n", i, block[i]);

    printf("\n");
}

unsigned int get_min_element(const unsigned int *block, unsigned short int len) {
    unsigned int min = block[0];
    for (int i = 1; i < len; i++)
        if (min > block[i])
            min = block[i];

    return min;
}

unsigned int get_max_element(const unsigned int *block, unsigned short int len) {
    unsigned int max = block[0];
    for (int i = 1; i < len; i++)
        if (max < block[i])
            max = block[i];

    return max;
}

unsigned int get_number_of_digits(unsigned int max) {
    unsigned int number_of_digits = 0;
    do {
        ++number_of_digits;
        max /= 2;
    } while (max);

    return number_of_digits;
}

void substract_min_to_block(unsigned int *block, unsigned int min, unsigned short int len) {
    for (int i = 0; i < len; i++)
        block[i] -= min;
}

bool is_valid_parameters(int argc, char **argv) {
    return true;
}

int main(int argc, char *argv[]) {
    if (!is_valid_parameters(argc, argv)) return 1;
    unsigned short int numbers_per_block = strtol(argv[1], NULL, 10);
    const char *input_file = argv[4];
    const char *output_file = argv[5];

    FILE *fin, *fout;
    fin = fopen(input_file, "rb");
    fout = fopen(output_file, "w");
    if ((fin == NULL) || (fout == NULL)) return EXIT_FAILURE;

    while (!feof(fin)) {
        unsigned int block[numbers_per_block];
        unsigned int i = 0;

        //obtiene los numeros del archivo
        while ((!feof(fin)) && (i < numbers_per_block)) {
            unsigned int x = 0;
            fread(&x, sizeof(unsigned int), 1, fin);
            block[i] = ntohl(x);
            i++;
        }
        if (i == 1) continue;

        //calcula el minimo, maximo, bits necesarios y resta diferencia
        unsigned int min = get_min_element(block, numbers_per_block);
        substract_min_to_block(block, min, numbers_per_block);
        unsigned int max = get_max_element(block, numbers_per_block);
        unsigned int number_of_digits = get_number_of_digits(max);

        //escribe el minimo y la cant de bits utilizados
        unsigned int min_big = htonl(min);
        fwrite(&min_big, sizeof(int), 1, fout);
        bitset<8> BSUsedBits(number_of_digits);
        fwrite(&BSUsedBits, 1, 1, fout);;

        //convierte la dif de numeros en bits
        string s;
        for (int q = 0; q < numbers_per_block; q++) {
            char buffer[number_of_digits];
            string s2 = std::bitset<12>(block[q]).to_string();
            s2.copy(buffer, number_of_digits, 12 - number_of_digits);
            s += buffer;
            while (s.length() >= 8) {
                std::bitset<8> outNum(s);
                fwrite(&outNum, 1, 1, fout);
                s.erase(0, 8);
            }
        }
    }


    fclose(fin);
    fclose(fout);
    return 0;
}
