#pragma once

#include <functional>
#include <map>
#include <string>

namespace util
{
class File;

class FileWatcher
{
public:
    FileWatcher();
    ~FileWatcher();

    void addFile(const File& file);
    void removeFile(const File& file);
    bool check();

private:
    std::map<File, time_t> m_files;
};
}
