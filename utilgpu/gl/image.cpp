#include "image.h"

#include <cassert>
#include <map>

#include <QGLWidget>
#include <QImage>

namespace util
{
QImage loadImage(const std::string& filename)
{
    const QImage image{QString::fromStdString(filename)};
    return QGLWidget::convertToGLFormat(image);
}

void saveImage(const std::vector<unsigned char>& data, const int& width,
               const int& height, const std::string& filename,
               const int channels)
{
    std::map<int, QImage::Format> formats{
        {1, QImage::Format_Grayscale8},
        {4, QImage::Format_ARGB32},
        {3, QImage::Format_RGB888},
    };
    const QImage image{data.data(), width, height, formats.at(channels)};
    const auto flippedImage = image.mirrored();
    const auto status = flippedImage.save(QString::fromStdString(filename));
    assert(status);
}
}
