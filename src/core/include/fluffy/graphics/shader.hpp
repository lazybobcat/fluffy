#pragma once

#include <fluffy/definitions.hpp>
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

enum class ShaderDataType
{
    None = 0,
    Int,
    Float,
    Bool,
    Transform,
    Vector2f,
    Vector3f,
    Vector4f,
    Vector2i,
    Vector3i,
    Vector4i,
    Vector2u,
    Vector3u,
    Vector4u,
};

namespace EnumNames {
const std::array<const char*, 3> ShaderType({ { "vertex", "geometry", "fragment" } });
}

class Shader
{
public:
    Shader()          = default;
    virtual ~Shader() = default;

    static Ref<Shader> create();

    virtual void loadFromFile(const Path& vextexFile, const Path& fragmentFile) = 0;
    virtual void enable()                                                       = 0;
    virtual void disable()                                                      = 0;

    virtual void bindUniform(const String& name, float value)     = 0;
    virtual void bindUniform(const String& name, int value)       = 0;
    virtual void bindUniform(const String& name, bool value)      = 0;
    virtual void bindUniform(const String& name, glm::mat4 value) = 0;
    virtual void bindUniform(const String& name, Transform value) = 0;
    virtual void bindUniform(const String& name, Color value)     = 0;
    virtual void bindUniform(const String& name, Vector2f value)  = 0;
    virtual void bindUniform(const String& name, Vector3f value)  = 0;
    virtual void bindUniform(const String& name, Vector4f value)  = 0;
    virtual void bindUniform(const String& name, Vector2i value)  = 0;
    virtual void bindUniform(const String& name, Vector3i value)  = 0;
    virtual void bindUniform(const String& name, Vector4i value)  = 0;
    virtual void bindUniform(const String& name, Vector2u value)  = 0;
    virtual void bindUniform(const String& name, Vector3u value)  = 0;
    virtual void bindUniform(const String& name, Vector4u value)  = 0;
};
}
