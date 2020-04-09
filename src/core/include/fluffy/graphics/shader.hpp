#pragma once

#include <fluffy/file/path.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

enum class ShaderType
{
    Vertex = 0,
    Geometry,
    Fragment,
};

namespace EnumNames {
const std::array<const char*, 6> ShaderType({ { "vertex", "geometry", "fragment" } });
}

class Shader
{
public:
    Shader()          = default;
    virtual ~Shader() = default;

    virtual void loadFromFile(const Path& vextexFile, const Path& fragmentFile) = 0;
    virtual void enable()                                                       = 0;
    virtual void disable()                                                      = 0;
};
}
