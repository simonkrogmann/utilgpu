#define NO_COMPILE_TIME_RESOURCES
#include "resource.h"

#include <iostream>

namespace util
{
Resource::Resource(const std::string& name, const std::string& content)
    : File{name, name}, m_content{content}

{
}

std::string Resource::content() const
{
    return m_content;
}
bool Resource::exists() const
{
    return true;
}
time_t Resource::timeStamp() const
{
    return 0;
}
}
