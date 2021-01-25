#include "opengl_render_target.hpp"
#include "opengl.hpp"
#include "opengl_texture.hpp"
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

/**********************************************************************************************************************/

OpenGLTextureRenderTarget::~OpenGLTextureRenderTarget()
{
    terminate();
}

void OpenGLTextureRenderTarget::onBind(Painter& painter)
{
    FLUFFY_PROFILE_FUNCTION();

    initialize();
    GlCall(glBindFramebuffer(GL_FRAMEBUFFER, mRendererId));
}

void OpenGLTextureRenderTarget::onUnbind(Painter& painter)
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void OpenGLTextureRenderTarget::initialize()
{
    if (mRendererId == 0) {
        FLUFFY_PROFILE_FUNCTION();

        GlCall(glGenFramebuffers(1, &mRendererId));
        GlCall(glBindFramebuffer(GL_FRAMEBUFFER, mRendererId));
        GlCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, dynamic_cast<OpenglTexture2D&>(*mTexture).getRendererId(), 0));

        if (mDepthTexture) {
            GlCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, dynamic_cast<OpenglTexture2D&>(*mDepthTexture).getRendererId(), 0));
        }

        FLUFFY_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Incomplete framebuffer");
    }
}

void OpenGLTextureRenderTarget::terminate()
{
    if (mRendererId != 0) {
        FLUFFY_PROFILE_FUNCTION();

        GlCall(glDeleteFramebuffers(1, &mRendererId));
        mRendererId = 0;
    }
}
