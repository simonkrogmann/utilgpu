#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace util
{
class CFLNode
{
public:
    static std::unique_ptr<CFLNode> parseCFL(std::string filename);

    CFLNode(const std::string& name, CFLNode* parent = nullptr, int level = -1);
    ~CFLNode();

    CFLNode* operator[](const std::string& key);
    CFLNode* parent();
    std::vector<std::unique_ptr<CFLNode>>& children();
    std::string name();
    std::vector<std::string> values();
    std::string value();

private:
    std::string m_name;
    CFLNode* const m_parent;
    const int m_level;
    std::vector<std::unique_ptr<CFLNode>> m_children;
    std::vector<std::string> m_values;
};

std::unique_ptr<CFLNode> parseCFL(std::string filename);
}
