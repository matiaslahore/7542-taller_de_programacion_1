//
// Created by mati on 19/9/19.
//

#include <mutex>
#include <fstream>
#include <vector>
#include <string>

#ifndef CMAKE_DEMO_FILEMANAGER_H
#define CMAKE_DEMO_FILEMANAGER_H

#define MAX_DIGITS 12
#define MIN_BITS_TO_SAVE 8
#define NUMBER_LENGHT 4

class FileManager {
private:
    unsigned int n, seek, length;
    std::string buffer_s;
    std::fstream fin, fout;
    std::mutex &m;
    std::vector<unsigned int> pos_threads;
public:
    FileManager(unsigned int n, unsigned int quantity_threads,
                unsigned int num_per_block, std::mutex &m);

    int startFileManager(const char *infile, const char *outfile);

    std::vector<uint32_t> getBlock(unsigned int thread_id);

    void saveStream(std::string s);

    ~FileManager();
};


#endif //CMAKE_DEMO_FILEMANAGER_H
