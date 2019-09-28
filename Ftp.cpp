//
// Created by mati on 25/9/19.
//

#include <string>
#include "Ftp.h"


Ftp::Ftp() {

}

bool Ftp::newFolder(char *folderName) {
    return this->directory.createFolder(folderName);
}

Ftp::~Ftp() {}

std::string Ftp::listFolders() {
    return this->directory.listFolders();
}

bool Ftp::removeFolder(char *folderName) {
    return this->directory.removeFolder(folderName);
}
