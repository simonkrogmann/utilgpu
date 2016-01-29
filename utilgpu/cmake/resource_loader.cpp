#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <functional>

#include <utilgpu/cpp/file.h>

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

    std::string projectName{argv[1]};
    util::File output{argv[2]};
    if (output.exists() && output.timeStamp() > mostRecentlyEdited)
    {
        // generated file is already up to date
        return 0;
    }

    std::ofstream file{argv[2]};
    file << "#pragma once\n#include <map>\n";
    file << "const long long " << projectName << " = "
         << std::hash<std::string>()(projectName) << ";";
    file << "template<> inline util::Resource loadResource<" << projectName
         << ">(const std::string& "
            "name) {";
    file << "std::map<std::string, std::string> resources {";
    bool firstRun = true;
    for (const auto& resource : resources)
    {
        if (!firstRun)
        {
            file << ",";
        }
        firstRun = false;
        file << "{\"" << resource.path << "\", R\"(" << resource.content()
             << ")\"}";
    }
    file << "}; return {name, resources.at(name)}; }";

    return 0;
}
