//
// Created by mati on 27/9/19.
//

#include <set>
#include <string>
#include "common_directory.h"

common_directory::common_directory() {
    this->directories = new std::set<std::string>();
}

bool common_directory::createFolder(const std::string &folderName) {
    Lock l(this->mtx);

    if (this->directories->find(folderName) != this->directories->end())
        return false;

    this->directories->insert(folderName);
    return true;
}

std::string common_directory::listFolders() {
    std::string response;
    std::set<std::string>::iterator itr;
    Lock l(this->mtx);

    for (const std::string &x: *this->directories)
        response += FOLDERS_META_DATA + x + "\n";

    return response;
}

bool common_directory::removeFolder(const std::string &folderName) {
    Lock l(this->mtx);

    if (this->directories->find(folderName) == this->directories->end())
        return false;

    this->directories->erase(folderName);
    return true;
}

common_directory::~common_directory() = default;
