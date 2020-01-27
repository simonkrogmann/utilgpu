#pragma once

#include <utilgpu/cpp/StateKeeper.h>

namespace util
{
namespace viewport
{
struct Viewport
{
    Viewport(const unsigned int& width, const unsigned int& height);
    Viewport(const int& x, const int& y, const unsigned int& width,
             const unsigned int& height);
    int x, y;
    unsigned int width, height;
};

Viewport get();

void set(const Viewport& data);

StateKeeper use(const Viewport& resolution);
}  // namespace viewport
}  // namespace util
