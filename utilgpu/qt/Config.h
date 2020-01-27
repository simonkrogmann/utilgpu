#pragma once

#include <map>
#include <string>
#include <vector>

#include <QSettings>

namespace util
{
class Config
{
public:
    Config(const std::string& organization, const std::string& name);
    ~Config();

    void load(const int argc, char* argv[]);

    template <typename T = std::string>
    T value(const std::string& key);
    template <typename T>
    void setValue(const std::string& key, const T& value);
    void setDefaults(const std::map<std::string, std::string>& defaults);
    std::vector<std::string> additionalArguments();

private:
    std::vector<std::string> toVector(const int& argc, char* argv[]);
    std::map<std::string, std::string> parseArguments(
        const std::vector<std::string>& arguments);
    void setValues(const std::map<std::string, std::string>& pairs);

    QSettings m_settings;
    std::vector<std::string> m_additionalArguments;
    std::map<std::string, std::string> m_defaults;
};

template <>
std::string Config::value(const std::string& key);

template <>
void Config::setValue(const std::string& key, const std::string& value);
}  // namespace util

#include <utilgpu/qt/Config.hpp>
