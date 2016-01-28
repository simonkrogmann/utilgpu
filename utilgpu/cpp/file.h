#pragma once

#include <string>

namespace util
{
std::string loadFile(const std::string& filename);
bool fileExists(const std::string& filename);
std::string directoryOf(const std::string& filename);

struct File
{
    File(const std::string& name, const std::string& path);
    std::string name;
    std::string path;
    virtual std::string content() const;
    std::string directory() const;
    virtual bool exists() const;
};
}
