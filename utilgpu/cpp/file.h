#pragma once

#include <string>

namespace util
{
std::string loadFile(const std::string& filename);
bool fileExists(const std::string& filename);
std::string directoryOf(const std::string& filename);

struct File
{
    std::string name;
    std::string path;
    std::string content() const;
    std::string directory() const;
    bool exists() const;
};
}
