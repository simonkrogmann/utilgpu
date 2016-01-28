#pragma once

#include <utilgpu/cpp/file.h>
#include <compile_time_resources.h>

namespace util
{
struct Resource : public File
{
    Resource(const std::string& name, const std::string& path);
    Resource(const std::string& path);
    virtual std::string content() const;
    virtual bool exists() const;
    virtual time_t timeStamp() const;
};
}

#include <utilgpu/cpp/resource.hpp>
