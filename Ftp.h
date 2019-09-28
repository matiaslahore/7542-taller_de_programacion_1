//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_FTP_H
#define CMAKE_DEMO_FTP_H


#include <string>
#include "Directory.h"

class Ftp {
private:
    Directory directory;
public:
    Ftp();

    bool newFolder(char *folderName);

    ~Ftp();

    std::string listFolders();

    bool removeFolder(char *folderName);
};


#endif //CMAKE_DEMO_FTP_H
