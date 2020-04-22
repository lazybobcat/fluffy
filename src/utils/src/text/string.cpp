#include <fluffy/pch.hpp>

void Fluffy::replaceAll(std::string& base, std::string& pattern, std::string& replacement)
{
    if (pattern.empty()) {
        return;
    }

    std::size_t startPosition = 0;
    while ((startPosition = base.find(pattern)) != std::string::npos) {
        base.replace(startPosition, pattern.length(), replacement);
        startPosition += replacement.length();
    }
}

std::string Fluffy::printString(const std::string& base, std::initializer_list<std::string> args)
{
    std::string output = base;
    int         i      = 1;
    for (auto arg : args) {
        std::string pattern = "%" + toString(i);
        replaceAll(output, pattern, arg);
        ++i;
    }

    return output;
}

std::vector<std::string> Fluffy::split(const std::string& base, char c)
{
    std::vector<std::string> strings;
    std::istringstream       f(base);
    std::string              s;
    while (std::getline(f, s, c)) {
        strings.push_back(s);
    }

    return strings;
}