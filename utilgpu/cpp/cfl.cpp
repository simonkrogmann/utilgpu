#include "cfl.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include <utilgpu/cpp/str.h>

namespace util
{
std::unique_ptr<CFLNode> parseCFL(const std::string& filename)
{
    return CFLNode::parseCFL(filename);
}

std::unique_ptr<CFLNode> CFLNode::parseCFL(const std::string& filename)
{
    auto root = std::make_unique<CFLNode>("root");
    auto current = root.get();

    std::ifstream sourceFile(filename);
    std::string line;
    int valueLevel = -1;
    unsigned int lineNumber = 1;
    bool directValue = false;
    unsigned int lastNodeLine = 0;

    // strings can span multiple lines
    bool stringMode = false;
    std::string collected = "";
    while (std::getline(sourceFile, line))
    {
        unsigned int lineBegin = lineNumber;
        auto level = static_cast<int>(leadingSpaces(line));
        line = line.substr(level);

        if (stringMode)
        {
            collected += " ";
        }

        bool explicitString = false;
        bool afterString = false;
        for (const auto& c : line)
        {
            // comment
            if (c == '#' && !stringMode) break;
            if (afterString && c != ' ')
            {
                return ErrorNode(lineNumber,
                                 "Only comments can follow strings.");
            }
            if (stringMode)
            {
                if (c == '"')
                {
                    stringMode = false;
                    afterString = true;
                }
                else
                {
                    collected += c;
                }
                continue;
            }
            lineBegin = lineNumber;
            if (c == ' ')
                continue;
            else if (c == '"')
            {
                assert(collected == "");
                stringMode = true;
                explicitString = true;
            }
            else if (c == ':')
            {
                // handle node
                const auto name = collected;
                if (name.empty())
                {
                    return ErrorNode(lineNumber, "Node names cannot be empty.");
                }
                while (current->m_level >= level)
                {
                    current = current->parent();
                }
                if (current->m_values.size() > 0)
                {
                    return ErrorNode(lineNumber,
                                     "Nodes cannot have children and values.");
                }
                current = current->addChild(name, level);
                valueLevel = -1;
                level += 1;
                directValue = false;
                lastNodeLine = lineNumber;
                collected = "";
            }
            else
            {
                collected += c;
            }
        }
        // handles the case, where someone explicitly specifies an empty string
        bool thereIsAString = collected.size() > 0 || explicitString;

        // save value into parent node
        if (!stringMode && thereIsAString)
        {
            if (directValue)
            {
                return ErrorNode(
                    lineNumber,
                    "A node with a direct value cannot have any other values.");
            }
            else if (valueLevel != -1 && valueLevel != level)
            {
                return ErrorNode(lineNumber,
                                 "All values of a node must be aligned.");
            }
            else if (level <= current->m_level)
            {
                return ErrorNode(lineNumber,
                                 "A value or its continuation must be indented "
                                 "deeper than its node.");
            }
            directValue = lastNodeLine == lineBegin;
            valueLevel = level;
            assert(current->m_children.size() == 0);
            current->m_values.push_back(collected);
            collected = "";
        }
        ++lineNumber;
    }
    return root;
}

CFLNode::CFLNode(const std::string& name, CFLNode* parent, const int& level)
    : m_name{name}, m_parent{parent}, m_level{level}
{
}

CFLNode::~CFLNode() {}

std::unique_ptr<CFLNode> CFLNode::ErrorNode(const unsigned int& lineNumber,
                                            const std::string& message)
{
    return std::make_unique<CFLNode>(
        "Error in line " + std::to_string(lineNumber) + ": " + message);
}

bool CFLNode::valid() const
{
    return m_name == "root" || m_level != -1;
}

std::string CFLNode::message() const
{
    assert(!valid());
    return m_name;
}

CFLNode* CFLNode::addChild(const std::string& name, const int& level)
{
    assert(valid());
    auto newNode = std::make_unique<CFLNode>(name, this, level);
    m_children.push_back(std::move(newNode));
    return m_children.back().get();
}

CFLNode* CFLNode::parent() const
{
    assert(valid());
    return m_parent;
}

const std::vector<std::unique_ptr<CFLNode>>& CFLNode::children() const
{
    assert(valid());
    return m_children;
}

std::string CFLNode::name() const
{
    assert(valid());
    return m_name;
}

const std::vector<std::string>& CFLNode::values() const
{
    assert(valid());
    return m_values;
}

std::string CFLNode::value(const std::string& defaultValue) const
{
    assert(valid());
    assert(!m_values.empty());
    if (m_values[0] == "")
    {
        return defaultValue;
    }
    return m_values[0];
}
float CFLNode::value(const float& defaultValue) const
{
    const auto stringValue = value();
    return (stringValue == "") ? defaultValue : std::stof(stringValue);
}
int CFLNode::value(const int& defaultValue) const
{
    const auto stringValue = value();
    return (stringValue == "") ? defaultValue : std::stoi(stringValue);
}

CFLNode* CFLNode::operator[](const std::string& key)
{
    assert(valid());
    for (auto& child : m_children)
    {
        if (child->name() == key)
        {
            return child.get();
        }
    }
    return nullptr;
}

void CFLNode::print() const
{
    for (int i = 0; i < m_level; ++i)
    {
        std::cout << " ";
    }
    std::cout << m_name << ": ";

    for (const auto& value : m_values)
    {
        std::cout << value << ", ";
    }
    std::cout << std::endl;
    for (const auto& child : m_children)
    {
        child->print();
    }
}

}  // namespace util
