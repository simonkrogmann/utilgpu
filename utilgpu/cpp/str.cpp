#include "str.h"

#include <cassert>
#include <sstream>
#include <string>

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

void replaceAll(std::string& target, const std::string& old,
                const std::string& with)
{
    size_t position;
    while ((position = target.find(old)) != std::string::npos)
    {
        target.replace(position, old.length(), with);
    }
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

std::vector<std::string> splitAll(const std::string& string,
                                  const std::string& at)
{
    std::vector<std::string> results;
    size_t lastPosition = 0;
    auto position = string.find(at);
    while (position != std::string::npos)
    {
        results.push_back(string.substr(lastPosition, position - lastPosition));
        position += at.size();
        lastPosition = position;
        position = string.find(at, position);
    }
    results.push_back(string.substr(lastPosition));
    return results;
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

std::string stripSpaces(const std::string& string)
{
    size_t begin = 0, end = string.size() - 1;
    for (; string[begin] == ' '; ++begin)
        ;
    for (; string[end] == ' '; --end)
        ;
    return string.substr(begin, end - begin + 1);
}

bool isWhitespace(const char c)
{
    std::string whitespaceCharacters = " \n\r\t";
    return whitespaceCharacters.find(c) != std::string::npos;
}

std::string stripWhitespace(const std::string& string)
{
    size_t begin = 0, end = string.size() - 1;
    for (; isWhitespace(string[begin]); ++begin)
        ;
    for (; isWhitespace(string[end]); --end)
        ;
    return string.substr(begin, end - begin + 1);
}

size_t leadingSpaces(const std::string& string)
{
    size_t number = 0;
    for (; string[number] == ' '; ++number)
        ;
    return number;
}
}
