#include "cfl.h"

#include <fstream>
#include <cassert>
#include <iostream>

#include "str.h"

namespace util
{
std::unique_ptr<CFLNode> parseCFL(std::string filename)
{
    return CFLNode::parseCFL(filename);
}

std::unique_ptr<CFLNode> CFLNode::parseCFL(std::string filename)
{
    auto root = std::make_unique<CFLNode>("root");
    auto current = root.get();

    std::ifstream sourceFile(filename);
    std::string line;
    while (std::getline(sourceFile, line))
    {
        auto level = static_cast<int>(leadingSpaces(line));
        line = line.substr(level);
        const auto commentPosition = line.find("#");
        if (commentPosition != std::string::npos)
        {
            line = line.substr(0, commentPosition);
        }
        const auto colonPosition = line.find(":");
        if (colonPosition != std::string::npos)
        {
            auto pair = split(line, ":");
            auto name = stripSpaces(pair.first);
            std::cout << level << name << std::endl;
            while (current->m_level >= level)
            {
                current = current->parent();
            }
            auto newNode = std::make_unique<CFLNode>(name, current, level);
            current->m_children.push_back(std::move(newNode));
            current = current->m_children.back().get();

            line = pair.second;
        }
        line = stripSpaces(line);
        if (line.size() > 0)
        {
            current->m_values.push_back(line);
        }
    }
    return root;
}
CFLNode::CFLNode(const std::string& name, CFLNode* parent, int level)
    : m_name{name}, m_parent{parent}, m_level{level}
{
}
CFLNode::~CFLNode()
{
}
CFLNode* CFLNode::parent()
{
    return m_parent;
}
std::vector<std::unique_ptr<CFLNode>>& CFLNode::children()
{
    return m_children;
}
std::string CFLNode::name()
{
    return m_name;
}
std::vector<std::string> CFLNode::values()
{
    return m_values;
}
std::string CFLNode::value()
{
    assert(m_values.size() > 0);
    return m_values[0];
}

CFLNode* CFLNode::operator[](const std::string& key)
{
    for (auto& child : m_children)
    {
        if (child->name() == key)
        {
            return child.get();
        }
    }
    m_children.push_back(std::make_unique<CFLNode>(key, this, m_level + 1));
    return m_children.back().get();
}
}
