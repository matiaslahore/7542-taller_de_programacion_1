//
// Created by mati on 25/9/19.
//

#include <string>
#include "common_ftp.h"


common_ftp::common_ftp() = default;

bool common_ftp::newFolder(char *folderName) {
    return this->dir.createFolder(folderName);
}

std::string common_ftp::listFolders() {
    return this->dir.listFolders();
}

bool common_ftp::removeFolder(char *folderName) {
    return this->dir.removeFolder(folderName);
}

common_ftp::~common_ftp() = default;
