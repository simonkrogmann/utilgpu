#include "FileWatcher.h"

#include <string>
#include <cassert>
#include <sys/stat.h>

#include <utilgpu/cpp/file.h>

namespace util
{
FileWatcher::FileWatcher() : m_files{}
{
}

FileWatcher::~FileWatcher()
{
}

void FileWatcher::addFile(const File& file)
{
    m_files[file] = file.timeStamp();
}

void FileWatcher::removeFile(const File& file)
{
    m_files.erase(file);
}

bool FileWatcher::check()
{
    bool changed = false;
    for (const auto& file : m_files)
    {
        const auto newTime = file.first.timeStamp();
        if (newTime != file.second)
        {
            m_files[file.first] = newTime;
            changed = true;
        }
    }
    return changed;
}
}
