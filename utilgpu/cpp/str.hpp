#pragma once

#include <utilgpu/cpp/str.h>

namespace util
{
template <typename T>
std::string format(std::string &str, T replace)
{
    util::replace(str, "@", std::to_string(replace));
    return str;
}

template <typename T, typename... T2>
std::string format(std::string &str, T replace, T2... rest)
{
    std::string temp = format(str, replace);
    return format(temp, rest...);
}

template <typename... T>
std::string format(const char *str, T... rest)
{
    std::string pattern{str};
    return format(pattern, rest...);
}
}  // namespace util
