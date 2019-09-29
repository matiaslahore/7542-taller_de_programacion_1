//
// Created by mati on 25/9/19.
//

#ifndef CMAKE_DEMO_COMMON_FTP_H
#define CMAKE_DEMO_COMMON_FTP_H


#include <string>
#include "common_directory.h"

class common_ftp {
private:
    common_directory dir;
public:
    common_ftp();

    bool newFolder(char *folderName);

    ~common_ftp();

    std::string listFolders();

    bool removeFolder(char *folderName);
};


#endif //CMAKE_DEMO_COMMON_FTP_H
