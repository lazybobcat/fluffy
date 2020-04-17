#include <fluffy/graphics/platform/opengl_texture.hpp>
#include <fluffy/graphics/renderer.hpp>
#include <fluffy/graphics/texture.hpp>

using namespace Fluffy;

Ref<Texture2D> Texture2D::create(const Path& path, const IntRect& area)
{
    switch (Renderer::RenderAPI) {
        case RenderAPIList::OpenGL:
            return std::make_shared<OpenglTexture2D>(path, area);

        case RenderAPIList::None:
            FLUFFY_LOG_ERROR("Shader for render API '" + toString(EnumNames::RenderAPI[(int)Renderer::RenderAPI]) + "' is not supported!");
            return nullptr;
    }

    FLUFFY_LOG_ERROR("Shader for render API '" + toString(EnumNames::RenderAPI[(int)Renderer::RenderAPI]) + "' is not supported!");
    return nullptr;
}
