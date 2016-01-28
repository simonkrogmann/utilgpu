#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include <utilgpu/cpp/file.h>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Not enough arguments." << std::endl;
        exit(1);
    }

    std::vector<util::File> resources;
    for (int i = 2; i < argc; ++i)
    {
        util::File resource{argv[i], argv[i]};
        if (!resource.exists())
        {
            std::cout << resource.path << " was not found." << std::endl;
            exit(1);
        }
        resources.push_back(resource);
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
        file << "{\"" << resource.name << "\",R\"(" << resource.content()
             << ")\"}";
    }
    file << "};";
}
