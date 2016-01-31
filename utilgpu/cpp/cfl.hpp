#pragma once

#include <utilgpu/cpp/cfl.h>

#include <cassert>

#include <utilgpu/cpp/str.h>

namespace util
{
template <size_t size>
std::array<float, size> CFLNode::valueVector(
    const std::array<float, size>& defaultValue) const
{
    const auto stringValue = value();
    std::array<float, size> results;
    if (stringValue == "")
    {
        results = defaultValue;
    }
    else
    {
        size_t i = 0;
        for (const auto& value : splitAll(stringValue, ","))
        {
            results[i++] = std::stof(value);
        }
        assert(i == 1 || i == size);
        if (i == 1)
        {
            results.fill(results[0]);
        }
    }
    return results;
}
}
