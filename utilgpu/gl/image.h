#pragma once

#include <QImage>
#include <string>

namespace util
{
QImage loadImage(const std::string& filename);
void saveImage(const std::vector<unsigned char>& data, const int& width,
               const int& height, const std::string& filename,
               const int channels = 4);
}
