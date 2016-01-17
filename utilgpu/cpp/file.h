#pragma once

#include <string>

namespace util
{
std::string loadFile(const std::string& filename);

struct File
{
    std::string name;
    std::string path;
    std::string content() const { return loadFile(path); }
};
}
