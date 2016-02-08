#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <functional>

#include <utilgpu/cpp/file.h>
#include <utilgpu/cpp/str.h>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <project> <output> <resources>"
                  << std::endl;
        return 1;
    }

    std::vector<util::File> resources;
    time_t mostRecentlyEdited = 0;
    for (int i = 3; i < argc; ++i)
    {
        util::File resource{argv[i]};
        if (!resource.exists())
        {
            std::cout << resource.path << " was not found." << std::endl;
            return 1;
        }
        mostRecentlyEdited = std::max(mostRecentlyEdited, resource.timeStamp());
        resources.push_back(resource);
    }

    const std::string projectName{argv[1]};
    util::File output{argv[2]};
    if (output.exists() && output.timeStamp() > mostRecentlyEdited)
    {
        // generated file is already up to date
        return 0;
    }

    std::string fileTemplate = R"(
#pragma once
#include <map>
#include <iostream>
const long long {{ProjectName}} = {{ProjectNameHash}};
template<> inline util::File loadResource<{{ProjectName}}>(const std::string& name)
{
    const std::map<std::string, std::string> resources {
        {{Resources}}
    };
    if (resources.find(name) == resources.end())
    {
        std::cout << "Resource not found: " << name << std::endl;
    }
    return {name, name, resources.at(name)};
}
)";

    std::ofstream file{argv[2]};
    auto hash = std::to_string(std::hash<std::string>()(projectName));
    util::replaceAll(fileTemplate, "{{ProjectName}}", projectName);
    util::replaceAll(fileTemplate, "{{ProjectNameHash}}", hash);
    bool firstRun = true;
    std::string resourceString = "";
    for (const auto& resource : resources)
    {
        if (!firstRun)
        {
            resourceString += ",";
        }
        firstRun = false;
        resourceString +=
            "{\"" + resource.path + "\", R\"(" + resource.content() + ")\"}";
    }
    util::replaceAll(fileTemplate, "{{Resources}}", resourceString);
    file << fileTemplate;

    return 0;
}
