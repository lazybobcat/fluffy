#pragma once

#include <fluffy/graphics/shader.hpp>

namespace Fluffy {

class OpenglShader : public Shader
{
public:
    OpenglShader();
    ~OpenglShader();

    void loadFromFile(const Path& vextexFile, const Path& fragmentFile) override;
    void enable() override;
    void disable() override;

    void bindUniform(const std::string& name, float value) override;
    void bindUniform(const std::string& name, int value) override;
    void bindUniform(const std::string& name, bool value) override;
    void bindUniform(const std::string& name, Transform value) override;
    void bindUniform(const std::string& name, Vector2f value) override;
    void bindUniform(const std::string& name, Vector3f value) override;
    void bindUniform(const std::string& name, Vector4f value) override;
    void bindUniform(const std::string& name, Vector2i value) override;
    void bindUniform(const std::string& name, Vector3i value) override;
    void bindUniform(const std::string& name, Vector4i value) override;
    void bindUniform(const std::string& name, Vector2u value) override;
    void bindUniform(const std::string& name, Vector3u value) override;
    void bindUniform(const std::string& name, Vector4u value) override;

private:
    void compile(const char* vertexShader, const char* fragmentShader);
    bool compileShaderCode(std::uint32_t shaderId, const char* code, ShaderType type) const;

private:
    std::uint32_t mProgramId;
};
}
