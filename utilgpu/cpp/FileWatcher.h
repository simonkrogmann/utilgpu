#pragma once

#include <string>
#include <map>
#include <functional>

#include <utilgpu/cpp/file.h>

namespace util
{
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
