#pragma once

#include <fluffy/graphics/shader.hpp>
#include <fluffy/graphics/transform.hpp>

namespace Fluffy {

class OpenglShader : public Shader
{
public:
    typedef unsigned int Id;

public:
    OpenglShader() = default;
    ~OpenglShader();

    void loadFromFile(const Path& vextexFile, const Path& fragmentFile) override;
    void enable() override;
    void disable() override;

    void bindUniform(const std::string& name, float value);
    void bindUniform(const std::string& name, int value);
    void bindUniform(const std::string& name, bool value);
    void bindUniform(const std::string& name, Transform value);
    // @todo other uniform types

private:
    void compile(const char* vertexShader, const char* fragmentShader);
    bool compileShaderCode(Id shaderId, const char* code, ShaderType type) const;

private:
    Id mVertexId, mFragmentId, mGeometryId;
    Id mProgramId;
};
}
