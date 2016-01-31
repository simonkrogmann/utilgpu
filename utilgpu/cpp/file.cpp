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
    assert(sourceFile.is_open());

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

File::File(const std::string& name, const std::string& path,
           const std::string& content)
    : name{name}, path{path}, m_content{content}, m_storesContent{true}
{
}

File::File(const std::string& name, const std::string& path)
    : name{name}, path{path}
{
}

File::File(const std::string& path) : File{rsplit(path, "/").second, path}
{
}

std::string File::content() const
{
    if (m_storesContent)
    {
        return m_content;
    }
    return loadFile(path);
}
bool File::exists() const
{
    if (m_storesContent)
    {
        return true;
    }
    return fileExists(path);
}

std::string File::directory() const
{
    return directoryOf(path);
}

time_t File::timeStamp() const
{
    if (m_storesContent)
    {
        return 0;
    }
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
