#include "Config.h"

#include <cassert>
#include <map>
#include <string>
#include <vector>

#include <utilgpu/cpp/str.h>
#include <QSettings>

namespace util
{
Config::Config(const std::string& organization, const std::string& name)
    : m_settings{QString::fromStdString(organization),
                 QString::fromStdString(name)}
{
}

Config::~Config()
{
}

template <>
std::string Config::value(const std::string& key)
{
    return value<QString>(key).toUtf8().constData();
}

template <>
void Config::setValue(const std::string& key, const std::string& value)
{
    setValue(key, QString::fromStdString(value));
}

void Config::load(const int argc, char* argv[])
{
    const auto arguments = toVector(argc, argv);
    const auto options = parseArguments(arguments);

    setValues(options);
}

void Config::setDefaults(const std::map<std::string, std::string>& defaults)
{
    m_defaults = defaults;
}

std::vector<std::string> Config::toVector(const int& argc, char* argv[])
{
    std::vector<std::string> arguments;
    for (int i = 0; i < argc; ++i)
    {
        arguments.push_back(argv[i]);
    }
    return arguments;
}

std::map<std::string, std::string> Config::parseArguments(
    const std::vector<std::string>& arguments)
{
    std::map<std::string, std::string> options;
    for (const auto& argument : arguments)
    {
        if (argument.substr(0, 2) == "--" && util::contains(argument, "="))
        {
            const auto split = util::split(argument.substr(2), "=");
            options[split.first] = split.second;
        }
        else
        {
            m_additionalArguments.push_back(argument);
        }
    }
    return options;
}

std::vector<std::string> Config::additionalArguments()
{
    return m_additionalArguments;
}

void Config::setValues(const std::map<std::string, std::string>& pairs)
{
    for (const auto& pair : pairs)
    {
        if (m_defaults.find(pair.first) != m_defaults.end())
        {
            m_settings.setValue(QString::fromStdString(pair.first),
                                QString::fromStdString(pair.second));
        }
    }
    m_settings.sync();
}
}
