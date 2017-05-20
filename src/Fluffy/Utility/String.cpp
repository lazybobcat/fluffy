//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#include <Fluffy/Utility/String.hpp>

void Fluffy::Utility::replaceAll(std::string& base, std::string& pattern, std::string& replacement)
{
    if (pattern.empty())
    {
        return;
    }

    std::size_t startPosition = 0;
    while ((startPosition = base.find(pattern)) != std::string::npos)
    {
        base.replace(startPosition, pattern.length(), replacement);
        startPosition += replacement.length();
    }
}

std::string Fluffy::Utility::printString(const std::string& base, std::initializer_list<std::string> args)
{
    std::string output = base;
    int i = 1;
    for (auto arg : args)
    {
        std::string pattern = "%" + toString(i);
        replaceAll(output, pattern, arg);
        ++i;
    }

    return output;
}