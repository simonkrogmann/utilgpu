#pragma once

#include <string>
#include <QImage>

namespace util
{
std::string loadFile(const std::string& filename);
QImage loadImage(const std::string& filename);
void saveImage(const std::vector<unsigned char>& data, const int& width,
               const int& height, const std::string& filename);

struct File
{
    std::string name;
    std::string path;
    std::string content() const { return loadFile(path); }
};
}
