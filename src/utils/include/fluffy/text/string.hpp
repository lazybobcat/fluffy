#pragma once

#define STRING(x) XSTR(x)
#define XSTR(s) #s

#include <fluffy/pch.hpp>

namespace Fluffy {

template<typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

void replaceAll(std::string& base, std::string& pattern, std::string& replacement);

/**
 * sprintf like : replaces occurrences of "%1", "%2", "%3", etc. by given string args
 * Usage: printString("Entity %1 received %2 damage", {"Skeleton762", "42"})
 *
 * @param std::string base
 * @param std::initializer_list<std::string> args
 * @return std::string
 */
std::string printString(const std::string& base, std::initializer_list<std::string> args);

/**
 * Split the string on the given char
 * Usage: split("/root/child", '/')
 * @param std::string base
 * @param char c
 * @return std::vector<std::string>
 */
std::vector<std::string> split(const std::string& base, char c);
}
