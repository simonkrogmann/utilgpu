#include "file.h"

#include <fstream>
#include <sstream>
#include <cassert>
#include <sys/stat.h>

#include "str.h"

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

std::string directoryOf(const std::string& filename)
{
    if (contains(filename, "/"))
    {
        return util::rsplit(filename, "/").first + "/";
    }
    return "";
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

std::string File::directory() const
{
    return directoryOf(path);
}
}
