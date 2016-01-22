#pragma once

#include <string>

namespace util
{
// replaces first occurence of old in target
void replace(std::string& target, const std::string& old,
             const std::string& with);

// splits string at first occurence
std::pair<std::string, std::string> split(const std::string& string,
                                          const std::string& at);
std::pair<std::string, std::string> rsplit(const std::string& string,
                                           const std::string& at);

bool contains(const std::string& string, const std::string& substring);
bool endsWith(const std::string& string, const std::string& ending);

std::pair<int, int> splitNumbers(const std::string& string,
                                 const std::string& at);

std::string stripSpaces(const std::string& string);
size_t leadingSpaces(const std::string& string);
}
