#include "opengl_video_module.hpp"
#include "opengl_painter.hpp"
#include "opengl_screen_render_target.hpp"
#include <fluffy/assert.hpp>
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

OpenGLVideoModule::OpenGLVideoModule(Window::Definition&& windowDefinition)
  : VideoModule(std::move(windowDefinition))
{}

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