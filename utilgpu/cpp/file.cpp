#include "file.h"

#include <fstream>
#include <sstream>
#include <cassert>
#include <sys/stat.h>

namespace util
{
std::string loadFile(const std::string& filename)
{
    std::ifstream sourceFile(filename);
    assert(!sourceFile.bad());

    std::stringstream sourceBuffer;
    sourceBuffer << sourceFile.rdbuf();
    return sourceBuffer.str();
}

bool fileExists(const std::string& filename)
{
    struct stat stats;
    return stat(filename.c_str(), &stats) == 0;
}

std::string File::content() const
{
    return loadFile(path);
}
bool File::exists() const
{
    return fileExists(path);
}
}
