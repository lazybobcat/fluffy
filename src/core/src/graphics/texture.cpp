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
        default:
            FLUFFY_LOG_ERROR("Texture for render API '{}' is not supported!", EnumNames::RenderAPI[(int)Renderer::RenderAPI]);
            return nullptr;
    }

    FLUFFY_LOG_ERROR("Texture for render API '{}' is not supported!", EnumNames::RenderAPI[(int)Renderer::RenderAPI]);
    return nullptr;
}
