#pragma once

#define STRING(x) XSTR(x)
#define XSTR(s) #s

#include <fmt/format.h>

namespace Fluffy {

using String = std::string;

/**
 * sprintf like : replaces occurrences of "{}", "{0}", "{1}", etc. by given string args
 * Usage: printString("Entity {} received {} damage", "Skeleton762", 42)
 *
 * @param base The base string with placeholders
 * @param args The arguments/variables to inject into the string
 *
 * @return The replaced string
 */
template<typename... Args>
inline String printString(const String& base, Args... args)
{
    return fmt::format(base, args...);
}
}
