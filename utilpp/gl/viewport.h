#pragma once

#include "../StateKeeper.h"

namespace util
{
namespace viewport
{
struct Viewport
{
    int x, y;
    unsigned int width, height;
};

Viewport get();

void set(const Viewport& data);

StateKeeper use(const Viewport& resolution);
}
}
