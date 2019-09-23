//
// Created by mati on 19/9/19.
//

#include <mutex>
#include <fstream>
#include <vector>

#ifndef CMAKE_DEMO_FILEMANAGER_H
#define CMAKE_DEMO_FILEMANAGER_H

using namespace std;

#define MAX_DIGITS 12
#define MIN_BITS_TO_SAVE 8
#define NUMBER_LENGHT 4

class FileManager {
private:
    unsigned int n, seek;
    string buffer_s;
    fstream fin, fout;
    mutex &m;
    vector<int> pos_threads;
public:
    FileManager(unsigned int n, unsigned int quantity_threads,
                unsigned int num_per_block, mutex &m);

    int startFileManager(const char *infile, const char *outfile);

    vector<unsigned int> getBlock(unsigned int thread_id);

    void saveStream(string s);

    ~FileManager();
};


#endif //CMAKE_DEMO_FILEMANAGER_H
