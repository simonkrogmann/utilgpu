#include "file.h"

#include <fstream>
#include <sstream>
#include <cassert>

namespace util
{
std::string loadFile(const std::string& filename)
{
    std::ifstream sourceFile(filename);
    assert(!sourceFile.bad());

    std::stringstream sourceBuffer;
    sourceBuffer << sourceFile.rdbuf();
    return sourceBuffer.str();
}
}
