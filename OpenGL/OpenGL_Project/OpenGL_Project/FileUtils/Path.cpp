#include "Path.h"

namespace Infrastructure {

PathFinder::PathFinder(const std::string& filePath) {
    CURRENT_FOLDER = [&]() {  
        using std::string;
        const char sep = '/';
        int i = (int) filePath.size() - 1;
        while (i >= 0 && filePath[i] != sep) i--; // remove /FILE_NAME.cpp
        
        return filePath.substr(0, i);
    }();
}

std::string PathFinder::getPath(const std::string& localPath) const {
    return CURRENT_FOLDER + localPath;
}
}
