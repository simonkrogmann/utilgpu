#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace util
{
// implements only a subset of yaml
class YAMLNode
{
public:
    static std::unique_ptr<YAMLNode> parseYAML(std::string filename);

    YAMLNode(YAMLNode* parent = nullptr, int level = -1)
        : m_parent{parent}, m_level{level}
    {
    }

    YAMLNode* operator[](const std::string& key);

    YAMLNode* parent() const { return m_parent; }
    const std::vector<std::pair<std::string, std::unique_ptr<YAMLNode>>>& children()
        const
    {
        return m_children;
    }
    const std::vector<std::string>& values() const { return m_values; }
    std::string value() const { return m_values[0]; }
private:
    YAMLNode* const m_parent;
    std::vector<std::pair<std::string, std::unique_ptr<YAMLNode>>> m_children;
    std::vector<std::string> m_values;
    const int m_level;
};

std::unique_ptr<YAMLNode> parseYAML(std::string filename);
}
