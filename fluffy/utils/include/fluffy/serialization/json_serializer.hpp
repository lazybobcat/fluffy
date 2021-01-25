#pragma once

#include <fluffy/file/path.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/serialization/serializable.hpp>

namespace Fluffy {

class JsonSerializer
{
public:
    static bool serializeToString(Fluffy::Serializable& input, String& output);
    static bool deserializeFromString(String& input, Fluffy::Serializable& output);
    static bool serializeToFile(Fluffy::Serializable& input, const Path& filepath);
    static bool deserializeFromFile(const Path& filepath, Fluffy::Serializable& output);
};
}
