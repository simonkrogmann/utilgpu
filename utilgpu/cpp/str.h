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

// The format functions are not very fast.
// Only use them for small strings or if performance does not matter.
std::string format(std::string& str, std::string replace);

std::string format(std::string& str, const char* replace);

template <typename T>
std::string format(std::string& str, T replace);

template <typename T, typename... T2>
std::string format(std::string& str, T replace, T2... rest);

template <typename... T>
std::string format(const char* str, T... rest);

// splits string at first occurrence
std::pair<std::string, std::string> split(const std::string& string,
                                          const std::string& at);
std::pair<std::string, std::string> rsplit(const std::string& string,
                                           const std::string& at);
std::vector<std::string> splitAll(const std::string& string,
                                  const std::string& at);

bool contains(const std::string& string, const std::string& substring);
bool startsWith(const std::string& string, const std::string& start);
bool endsWith(const std::string& string, const std::string& ending);

std::pair<int, int> splitNumbers(const std::string& string,
                                 const std::string& at);

bool isWhitespace(const char* c);
std::string stripWhitespace(const std::string& string);
std::string stripSpaces(const std::string& string);
size_t leadingSpaces(const std::string& string);
}  // namespace util

#include <utilgpu/cpp/str.hpp>
