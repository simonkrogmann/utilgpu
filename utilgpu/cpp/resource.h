#pragma once

#include <utilgpu/cpp/file.h>

namespace util
{
struct Resource : public File
{
    Resource(const std::string& name, const std::string& content);
    virtual std::string content() const override;
    virtual bool exists() const override;
    virtual time_t timeStamp() const override;

private:
    std::string m_content;
};
}

template <long long i>
util::Resource loadResource(const std::string& name)
{
    static_assert(i == 0, "No such project to include from.");
    return {name, ""};
}

#ifndef NO_COMPILE_TIME_RESOURCES
#include <compile_time_resources.h>
#endif
