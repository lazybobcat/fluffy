#include <fluffy/graphics/platform/glfw_window.hpp>
#include <fluffy/graphics/renderer.hpp>
#include <fluffy/graphics/window.hpp>

using namespace Fluffy;

Unique<Window> Window::create(const Window::Definition& definition)
{
    switch (Renderer::RenderAPI) {
        case RenderAPIList::OpenGL:
            return CreateUnique<GlfwWindow>(definition);

        case RenderAPIList::None:
        default:
            FLUFFY_LOG_ERROR("Window for render API '{}' is not supported!", EnumNames::RenderAPI[(int)Renderer::RenderAPI]);
            return nullptr;
    }

    FLUFFY_LOG_ERROR("Window for render API '{}' is not supported!", EnumNames::RenderAPI[(int)Renderer::RenderAPI]);
    return nullptr;
}
