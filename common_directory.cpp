//
// Created by mati on 27/9/19.
//

#include "common_directory.h"

common_directory::common_directory() {

}

common_directory::~common_directory() {

}

bool common_directory::createFolder(char *folderName) {
    std::string strToInsert(folderName);

    if (this->directories.find(strToInsert) != this->directories.end())
        return false;

    this->directories.insert(strToInsert);
    return true;
}

std::string common_directory::listFolders() {
    std::string response;
    std::unordered_set<std::string>::iterator itr;

    for (const std::string &x: this->directories)
        response += FOLDERS_META_DATA + x + "\n";

    return response;
}

bool common_directory::removeFolder(char *folderName) {
    std::string strToRemove(folderName);

    if (this->directories.find(strToRemove) == this->directories.end())
        return false;

    this->directories.erase(strToRemove);
    return true;
}
