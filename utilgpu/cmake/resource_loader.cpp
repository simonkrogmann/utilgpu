#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include <utilgpu/cpp/file.h>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <output> <resources>"
                  << std::endl;
        return 1;
    }

    std::vector<util::File> resources;
    time_t mostRecentlyEdited = 0;
    for (int i = 2; i < argc; ++i)
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

    util::File output{argv[1]};
    if (output.exists() && output.timeStamp() > mostRecentlyEdited)
    {
        // generated file is already up to date
        return 0;
    }

    std::ofstream file{argv[1]};
    file << "#pragma once\nstd::map<std::string, std::string> g_resources={";
    bool firstRun = true;
    for (const auto& resource : resources)
    {
        if (!firstRun)
        {
            file << ",";
        }
        firstRun = false;
        file << "{\"" << resource.path << "\",R\"(" << resource.content()
             << ")\"}";
    }
    file << "};";

    return 0;
}
