#pragma once

#include <string>
#include <vector>

namespace util
{
// replaces first occurrence of old in target
void replace(std::string& target, const std::string& old,
             const std::string& with);
void replaceAll(std::string& target, const std::string& old,
                const std::string& with);

// splits string at first occurrence
std::pair<std::string, std::string> split(const std::string& string,
                                          const std::string& at);
std::pair<std::string, std::string> rsplit(const std::string& string,
                                           const std::string& at);
std::vector<std::string> splitAll(const std::string& string,
                                  const std::string& at);

bool contains(const std::string& string, const std::string& substring);
bool endsWith(const std::string& string, const std::string& ending);

std::pair<int, int> splitNumbers(const std::string& string,
                                 const std::string& at);

bool isWhitespace(const char* c);
std::string stripWhitespace(const std::string& string);
std::string stripSpaces(const std::string& string);
size_t leadingSpaces(const std::string& string);
}
