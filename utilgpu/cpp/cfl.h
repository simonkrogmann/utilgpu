#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace util
{
class CFLNode
{
public:
    static std::unique_ptr<CFLNode> parseCFL(const std::string& filename);
    static std::unique_ptr<CFLNode> ErrorNode(const unsigned int& lineNumber,
                                              const std::string& message);

    CFLNode(const std::string& name, CFLNode* parent = nullptr,
            const int& level = -1);
    ~CFLNode();

    CFLNode* operator[](const std::string& key);
    CFLNode* parent() const;
    const std::vector<std::unique_ptr<CFLNode>>& children() const;
    std::string name() const;
    const std::vector<std::string>& values() const;
    std::string value(const std::string& defaultValue = "") const;
    float value(const float& defaultValue) const;
    int value(const int& defaultValue) const;
    template <size_t size>
    std::array<float, size> valueVector(
        const std::array<float, size>& defaultValue) const;
    bool valid() const;
    std::string message() const;

    void print() const;

private:
    CFLNode* addChild(const std::string& name, const int& level);

    std::string m_name;
    CFLNode* const m_parent;
    const int m_level;
    std::vector<std::unique_ptr<CFLNode>> m_children;
    std::vector<std::string> m_values;
};

std::unique_ptr<CFLNode> parseCFL(const std::string& filename);
}  // namespace util

#include <utilgpu/cpp/cfl.hpp>
