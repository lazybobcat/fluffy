#include <fluffy/graphics/platform/opengl_shader.hpp>
#include <fluffy/graphics/renderer.hpp>
#include <fluffy/graphics/shader.hpp>

using namespace Fluffy;

std::shared_ptr<Shader> Shader::create()
{
    switch (Renderer::RenderAPI) {
        case RenderAPIList::OpenGL:
            return std::make_shared<OpenglShader>();

        case RenderAPIList::None:
            FLUFFY_LOG_ERROR("Shader for render API '" + toString(EnumNames::RenderAPI[(int)Renderer::RenderAPI]) + "' is not supported!");
            return nullptr;
    }

    FLUFFY_LOG_ERROR("Shader for render API '" + toString(EnumNames::RenderAPI[(int)Renderer::RenderAPI]) + "' is not supported!");
    return nullptr;
}
