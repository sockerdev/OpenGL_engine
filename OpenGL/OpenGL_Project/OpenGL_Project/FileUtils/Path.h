#pragma once

#include <string>

namespace Infrastructure {

class PathFinder {
public:
    PathFinder(const std::string& where);
    
    std::string getPath(const std::string& localPath) const;
private:
    std::string CURRENT_FOLDER;
};
}

