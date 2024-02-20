#pragma once

#include <utilgpu/cpp/file.h>

namespace util
{
template <unsigned long long i>
util::File loadResource(const std::string& name)
{
    static_assert(i == 0ull, "No such project to include from.");
    return {name, ""};
}
}  // namespace util

#ifndef NO_COMPILE_TIME_RESOURCES
#include <compile_time_resources.h>
#endif
