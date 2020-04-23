#include <fluffy/graphics/platform/opengl_shader.hpp>
#include <fluffy/graphics/renderer.hpp>
#include <fluffy/graphics/shader.hpp>

using namespace Fluffy;

Ref<Shader> Shader::create()
{
    switch (Renderer::RenderAPI) {
        case RenderAPIList::OpenGL:
            return std::make_shared<OpenglShader>();

        case RenderAPIList::None:
            FLUFFY_LOG_ERROR("Shader for render API '{}' is not supported!", EnumNames::RenderAPI[(int)Renderer::RenderAPI]);
            return nullptr;
    }

    FLUFFY_LOG_ERROR("Shader for render API '{}' is not supported!", EnumNames::RenderAPI[(int)Renderer::RenderAPI]);
    return nullptr;
}
