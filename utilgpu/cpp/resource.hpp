#pragma once

#include <utilgpu/cpp/resource.h>

namespace util
{
std::string Resource::content() const
{
    return g_resources.at(path);
}
bool Resource::exists() const
{
    return g_resources.find(path) != g_resources.end();
}

Resource::Resource(const std::string& name, const std::string& path)
    : File{name, path}
{
}
}
