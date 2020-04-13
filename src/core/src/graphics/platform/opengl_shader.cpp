#include <fluffy/graphics/platform/opengl_shader.hpp>
#include <fluffy/graphics/platform/opengl.hpp>

using namespace Fluffy;

bool getFileContents(const std::string& filename, std::vector<char>& buffer)
{
    std::ifstream file(filename.c_str(), std::ios_base::binary);
    if (file)
    {
        file.seekg(0, std::ios_base::end);
        std::streamsize size = file.tellg();
        if (size > 0)
        {
            file.seekg(0, std::ios_base::beg);
            buffer.resize(static_cast<std::size_t>(size));
            file.read(&buffer[0], size);
        }
        buffer.push_back('\0');
        return true;
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OpenglShader::~OpenglShader()
{

}

void OpenglShader::loadFromFile(const Path& vextexFile, const Path& fragmentFile)
{
    std::vector<char> vertexShader, fragmentShader;

    if (!getFileContents(vextexFile.toString(), vertexShader)) {
        FLUFFY_LOG_ERROR("Failed to open vertex shader from file '" + vextexFile.toString() + "'");

        return;
    }
    FLUFFY_LOG_INFO("Loaded vertex shader from file '" + vextexFile.toString() + "'");

    if (!getFileContents(fragmentFile.toString(), fragmentShader)) {
        FLUFFY_LOG_ERROR("Failed to open fragment shader from file " + fragmentFile.toString());

        return;
    }
    FLUFFY_LOG_INFO("Loaded fragment shader from file '" + fragmentFile.toString() + "'");

    compile(&vertexShader[0], &fragmentShader[0]);
}

void OpenglShader::compile(const char* vertexShader, const char* fragmentShader)
{
    mVertexId = glCreateShader(GL_VERTEX_SHADER);
    if (!compileShaderCode(mVertexId, vertexShader, ShaderType::Vertex)) {
        return;
    }

    mFragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    if (!compileShaderCode(mFragmentId, fragmentShader, ShaderType::Fragment)) {
        return;
    }

    mProgramId = glCreateProgram();
    glAttachShader(mProgramId, mVertexId);
    glAttachShader(mProgramId, mFragmentId);

    int success;
    char infoLog[512];
    glLinkProgram(mProgramId);
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(mProgramId, 512, nullptr, infoLog);
        FLUFFY_LOG_ERROR("Failed to link shader program : " + toString(infoLog));
    }

    glDeleteShader(mVertexId);
    glDeleteShader(mFragmentId);
}

bool OpenglShader::compileShaderCode(Id shaderId, const char* code, ShaderType type) const
{
    int  success;
    char infoLog[512];
    glShaderSource(shaderId, 1, &code, nullptr);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        FLUFFY_LOG_ERROR("Failed to compile " + toString(EnumNames::ShaderType[(int)type]) + " shader : " + code);

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
}

void OpenglShader::bindUniform(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(mProgramId, name.c_str()), value);
}

void OpenglShader::bindUniform(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(mProgramId, name.c_str()), value);
}

void OpenglShader::bindUniform(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(mProgramId, name.c_str()), (int)value);
}

void OpenglShader::bindUniform(const std::string& name, Transform value)
{
    glUniformMatrix4fv(glGetUniformLocation(mProgramId, name.c_str()), 1, GL_FALSE, value.getData());
}
