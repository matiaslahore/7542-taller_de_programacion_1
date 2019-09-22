//
// Created by mati on 19/9/19.
//

#include <fstream>
#include <vector>

#ifndef CMAKE_DEMO_FILEMANAGER_H
#define CMAKE_DEMO_FILEMANAGER_H

using namespace std;

#define MAX_DIGITS 12
#define MAX_BLOCKS 8
#define MIN_BITS_TO_SAVE 8



class FileManager {
private:
    unsigned int n, seeks;
    string buffer_s;
    fstream fin, fout;
public:
    FileManager(unsigned int n, unsigned int seeks);

    int startFileManager(const char *infile, const char *outfile);

    vector<unsigned int> getBlock();

    void saveStream(string s);

    ~FileManager();
};


#endif //CMAKE_DEMO_FILEMANAGER_H
