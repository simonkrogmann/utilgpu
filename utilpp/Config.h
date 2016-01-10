#pragma once

#include <QSettings>
#include <map>
#include <string>
#include <vector>

namespace util {
class Config
{
public:
    Config(const std::string& organization, const std::string& name);
    ~Config();

    void load(const int argc, char* argv[]);

    std::string value(const std::string& key);
    unsigned int valueUInt(const std::string& key);
    void setValue(const std::string& key, const unsigned int& value);
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
}
