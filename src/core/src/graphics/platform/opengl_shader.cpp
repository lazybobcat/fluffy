#include <fluffy/graphics/platform/opengl.hpp>
#include <fluffy/graphics/platform/opengl_shader.hpp>

using namespace Fluffy;

bool getFileContents(const String& filename, std::vector<char>& buffer)
{
    std::ifstream file(filename.c_str(), std::ios_base::binary);
    if (file) {
        file.seekg(0, std::ios_base::end);
        std::streamsize size = file.tellg();
        if (size > 0) {
            file.seekg(0, std::ios_base::beg);
            buffer.resize(static_cast<std::size_t>(size));
            file.read(&buffer[0], size);
        }
        buffer.push_back('\0');
        return true;
    } else {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OpenglShader::OpenglShader()
{
    mProgramId = glCreateProgram();
}

OpenglShader::~OpenglShader()
{
    glDeleteProgram(mProgramId);
}

void OpenglShader::loadFromFile(const Path& vextexFile, const Path& fragmentFile)
{
    std::vector<char> vertexShader, fragmentShader;

    if (!getFileContents(vextexFile.toString(), vertexShader)) {
        FLUFFY_LOG_ERROR("Failed to open vertex shader from file '{}'", vextexFile);

        return;
    }
    FLUFFY_LOG_INFO("Loaded vertex shader from file '{}'", vextexFile);

    if (!getFileContents(fragmentFile.toString(), fragmentShader)) {
        FLUFFY_LOG_ERROR("Failed to open fragment shader from file '{}'", fragmentFile);

        return;
    }
    FLUFFY_LOG_INFO("Loaded fragment shader from file '{}'", fragmentFile);

    compile(&vertexShader[0], &fragmentShader[0]);
}

void OpenglShader::compile(const char* vertexShader, const char* fragmentShader)
{
    std::uint32_t vertexId, fragmentId;

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    if (!compileShaderCode(vertexId, vertexShader, ShaderType::Vertex)) {
        return;
    }

    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    if (!compileShaderCode(fragmentId, fragmentShader, ShaderType::Fragment)) {
        return;
    }

    glAttachShader(mProgramId, vertexId);
    glAttachShader(mProgramId, fragmentId);

    int  success;
    char infoLog[512];
    glLinkProgram(mProgramId);
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mProgramId, 512, nullptr, infoLog);
        FLUFFY_LOG_ERROR("Failed to link shader program : {}", infoLog);
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

bool OpenglShader::compileShaderCode(std::uint32_t shaderId, const char* code, ShaderType type) const
{
    int  success;
    char infoLog[512];
    glShaderSource(shaderId, 1, &code, nullptr);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        FLUFFY_LOG_ERROR("Failed to compile {} shader:\n{}", EnumNames::ShaderType[(int)type], code);

        return false;
    };

    return true;
}

void OpenglShader::enable()
{
    glUseProgram(mProgramId);
}

void OpenglShader::disable()
{
    glUseProgram(0);
}

void OpenglShader::bindUniform(const String& name, float value)
{
    glUniform1f(glGetUniformLocation(mProgramId, name.c_str()), value);
}

void OpenglShader::bindUniform(const String& name, int value)
{
    glUniform1i(glGetUniformLocation(mProgramId, name.c_str()), value);
}

void OpenglShader::bindUniform(const String& name, bool value)
{
    glUniform1i(glGetUniformLocation(mProgramId, name.c_str()), (int)value);
}

void OpenglShader::bindUniform(const String& name, Transform value)
{
    glUniformMatrix4fv(glGetUniformLocation(mProgramId, name.c_str()), 1, GL_FALSE, value.getData());
}

void OpenglShader::bindUniform(const String& name, Vector2f value)
{
    glUniform2f(glGetUniformLocation(mProgramId, name.c_str()), value.x, value.y);
}

void OpenglShader::bindUniform(const String& name, Vector3f value)
{
    glUniform3f(glGetUniformLocation(mProgramId, name.c_str()), value.x, value.y, value.z);
}

void OpenglShader::bindUniform(const String& name, Vector4f value)
{
    glUniform4f(glGetUniformLocation(mProgramId, name.c_str()), value.r, value.g, value.b, value.a);
}

void OpenglShader::bindUniform(const String& name, Vector2i value)
{
    glUniform2i(glGetUniformLocation(mProgramId, name.c_str()), value.x, value.y);
}

void OpenglShader::bindUniform(const String& name, Vector3i value)
{
    glUniform3i(glGetUniformLocation(mProgramId, name.c_str()), value.x, value.y, value.z);
}

void OpenglShader::bindUniform(const String& name, Vector4i value)
{
    glUniform4i(glGetUniformLocation(mProgramId, name.c_str()), value.r, value.g, value.b, value.a);
}

void OpenglShader::bindUniform(const String& name, Vector2u value)
{
    glUniform2ui(glGetUniformLocation(mProgramId, name.c_str()), value.x, value.y);
}

void OpenglShader::bindUniform(const String& name, Vector3u value)
{
    glUniform3ui(glGetUniformLocation(mProgramId, name.c_str()), value.x, value.y, value.z);
}

void OpenglShader::bindUniform(const String& name, Vector4u value)
{
    glUniform4ui(glGetUniformLocation(mProgramId, name.c_str()), value.r, value.g, value.b, value.a);
}
