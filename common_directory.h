//
// Created by mati on 27/9/19.
//

#ifndef CMAKE_DEMO_directory_H
#define CMAKE_DEMO_directory_H

#include <mutex>
#include "Lock.h"
#include <string>
#include <set>

#define FOLDERS_META_DATA "drwxrwxrwx 0 1000 4096 Sep 24 12:34 "

class common_directory {
private:
    std::mutex mtx;
    std::set<std::string> *directories;

public:
    common_directory();

    bool createFolder(char *folderName);

    ~common_directory();

    std::string listFolders();

    bool removeFolder(char *folderName);
};


#endif //CMAKE_DEMO_directory_H
