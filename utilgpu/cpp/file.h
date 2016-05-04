#pragma once

#include <string>

namespace util
{
std::string loadFile(const std::string& filename);
void writeFile(const std::string& filename, const std::string& content);
bool fileExists(const std::string& filename);
std::string directoryOf(const std::string& filename);

class File
{
public:
    File(const std::string& name, const std::string& path,
         const std::string& content);
    File(const std::string& name, const std::string& path);
    File(const std::string& path);
    std::string content() const;
    void setContent(const std::string& content) const;
    std::string directory() const;
    bool exists() const;
    time_t timeStamp() const;
    bool operator<(const File& other) const;

    std::string name;
    std::string path;

private:
    std::string m_content = "";
    bool m_storesContent = false;
};
}
