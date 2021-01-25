#include "opengl_screen_render_target.hpp"
#include "opengl.hpp"
#include <fluffy/profiling/profiler.hpp>

OpenGLScreenRenderTarget::OpenGLScreenRenderTarget(const IntRect& viewport)
  : ScreenRenderTarget(viewport)
{}

void OpenGLScreenRenderTarget::onBind(Painter& painter)
{
    FLUFFY_PROFILE_FUNCTION();

    // This unbinds any framebuffers so OpenGL will default draw calls to the screen
    GlCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
