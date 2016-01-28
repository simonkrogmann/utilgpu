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

File::File(const std::string& name, const std::string& path)
    : name{name}, path{path}
{
}

File::File(const std::string& path) : File{rsplit(path, "/").second, path}
{
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

time_t File::timeStamp() const
{
    struct stat stats;
    const auto error = stat(path.c_str(), &stats);
    assert(error == 0);
    return stats.st_mtime;
}
bool File::operator<(const File& other) const
{
    return path < other.path;
}
}
