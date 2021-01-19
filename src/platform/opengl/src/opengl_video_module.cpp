#include "opengl_video_module.hpp"
#include "../../glfw/src/glfw_window.hpp"
#include "opengl_painter.hpp"
#include "opengl_screen_render_target.hpp"
#include <fluffy/assert.hpp>
#include <fluffy/profiling/profiler.hpp>
#include <opengl.hpp>

using namespace Fluffy;

OpenGLVideoModule::OpenGLVideoModule(Window::Definition&& windowDefinition)
  : VideoModule(std::move(windowDefinition))
{
}

Unique<ScreenRenderTarget> OpenGLVideoModule::createScreenRenderTarget()
{
    FLUFFY_ASSERT(nullptr != mWindow, "Cannot create a RenderTarget if Window is not created yet!");

    auto    size     = mWindow->getSize();
    IntRect viewport = { size / 2, size };

    return CreateUnique<OpenGLScreenRenderTarget>(viewport);
}

Unique<Painter> OpenGLVideoModule::createPainter()
{
    return CreateUnique<OpenGLPainter>();
}

void OpenGLVideoModule::beginRender()
{
    FLUFFY_PROFILE_FUNCTION();
}

void OpenGLVideoModule::endRender()
{
    FLUFFY_PROFILE_FUNCTION();
    mWindow->swapBuffers();
}

int OpenGLVideoModule::getMaxTextureSlots()
{
    static int slots = 2; // Init it to 2 just in case the gl call doesn't work for some reason, so that we can still bind some textures
    GlCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &slots));

    return slots;
}

Unique<Window> OpenGLVideoModule::createWindow(const Window::Definition& definition)
{
    auto window =  CreateUnique<GlfwWindow>(definition);

    FLUFFY_LOG_INFO("GPU information:");
    FLUFFY_LOG_INFO("> Vendor: {}", glGetString(GL_VENDOR));
    FLUFFY_LOG_INFO("> Renderer: {}", glGetString(GL_RENDERER));
    FLUFFY_LOG_INFO("> Version: {}", glGetString(GL_VERSION));
    FLUFFY_LOG_INFO("> Max texture slots: {}", getMaxTextureSlots());

    return window;
}
