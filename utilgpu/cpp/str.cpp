#include "string.h"

#include <string>
#include <sstream>
#include <cassert>

namespace util
{
// replaces first occurrence of old in target
void replace(std::string& target, const std::string& old,
             const std::string& with)
{
    const auto position = target.find(old);
    assert(position != std::string::npos);
    target.replace(position, old.length(), with);
}

// splits string at first occurrence
std::pair<std::string, std::string> split(const std::string& string,
                                          const std::string& at)
{
    const auto position = string.find(at);
    if (position == std::string::npos)
    {
        return {string, ""};
    }
    return {string.substr(0, position), string.substr(position + at.length())};
}

std::pair<std::string, std::string> rsplit(const std::string& string,
                                           const std::string& at)
{
    const auto position = string.rfind(at);
    if (position == std::string::npos)
    {
        return {"", string};
    }
    return {string.substr(0, position), string.substr(position + at.length())};
}

bool contains(const std::string& string, const std::string& substring)
{
    return string.find(substring) != std::string::npos;
}

bool endsWith(const std::string& string, const std::string& ending)
{
    if (string.size() < ending.size())
    {
        return false;
    }
    return std::equal(ending.rbegin(), ending.rend(), string.rbegin());
}

std::pair<int, int> splitNumbers(const std::string& string,
                                 const std::string& at)
{
    const auto numbers = util::split(string, at);
    int first = 0, second = 0;
    std::istringstream(numbers.first) >> first;
    std::istringstream(numbers.second) >> second;
    return {first, second};
}
}
