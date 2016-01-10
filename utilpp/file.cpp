#include "file.h"

#include <fstream>
#include <sstream>
#include <cassert>

#include <QImage>
#include <QGLWidget>

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

QImage loadImage(const std::string& filename)
{
    const QImage image{QString::fromStdString(filename)};
    return QGLWidget::convertToGLFormat(image);
}

void saveImage(const std::vector<unsigned char>& data, const int& width,
               const int& height, const std::string& filename)
{
    const QImage image{data.data(), width, height, QImage::Format_ARGB32};
    const auto flippedImage = image.mirrored();
    const auto status = flippedImage.save(QString::fromStdString(filename));
    assert(status);
}
}
