#pragma once

#include <fluffy/file/path.hpp>
#include <fluffy/graphics/transform.hpp>
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

    static std::shared_ptr<Shader> create();

    virtual void loadFromFile(const Path& vextexFile, const Path& fragmentFile) = 0;
    virtual void enable()                                                       = 0;
    virtual void disable()                                                      = 0;

    virtual void bindUniform(const std::string& name, float value)     = 0;
    virtual void bindUniform(const std::string& name, int value)       = 0;
    virtual void bindUniform(const std::string& name, bool value)      = 0;
    virtual void bindUniform(const std::string& name, Transform value) = 0;
    virtual void bindUniform(const std::string& name, Vector2f value)  = 0;
    virtual void bindUniform(const std::string& name, Vector3f value)  = 0;
    virtual void bindUniform(const std::string& name, Vector4f value)  = 0;
    virtual void bindUniform(const std::string& name, Vector2i value)  = 0;
    virtual void bindUniform(const std::string& name, Vector3i value)  = 0;
    virtual void bindUniform(const std::string& name, Vector4i value)  = 0;
    virtual void bindUniform(const std::string& name, Vector2u value)  = 0;
    virtual void bindUniform(const std::string& name, Vector3u value)  = 0;
    virtual void bindUniform(const std::string& name, Vector4u value)  = 0;
};
}
