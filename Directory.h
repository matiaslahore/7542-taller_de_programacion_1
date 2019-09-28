//
// Created by mati on 27/9/19.
//

#ifndef CMAKE_DEMO_DIRECTORY_H
#define CMAKE_DEMO_DIRECTORY_H

#include <string>
#include <unordered_set>

#define FOLDERS_META_DATA "drwxrwxrwx 0 1000 4096 Sep 24 12:34 "

class Directory {
private:
    std::unordered_set<std::string> directories;
public:
    Directory();

    bool createFolder(char *folderName);

    ~Directory();

    std::string listFolders();

    bool removeFolder(char *folderName);
};


#endif //CMAKE_DEMO_DIRECTORY_H
