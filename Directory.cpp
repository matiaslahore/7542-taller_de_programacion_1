//
// Created by mati on 27/9/19.
//

#include "Directory.h"

Directory::Directory() {

}

Directory::~Directory() {

}

bool Directory::createFolder(char *folderName) {
    std::string strToInsert(folderName);

    if (this->directories.find(strToInsert) != this->directories.end())
        return false;

    this->directories.insert(strToInsert);
    return true;
}

std::string Directory::listFolders() {
    std::string response;
    std::unordered_set<std::string>::iterator itr;

    for (const std::string &x: this->directories)
        response += FOLDERS_META_DATA + x + "\n";

    return response;
}

bool Directory::removeFolder(char *folderName) {
    std::string strToRemove(folderName);

    if (this->directories.find(strToRemove) == this->directories.end())
        return false;

    this->directories.erase(strToRemove);
    return true;
}
