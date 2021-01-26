#include "opengl_painter.hpp"
#include "opengl.hpp"
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

void OpenGLPainter::clear(const Color& color)
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glClearColor(color.value.r, color.value.g, color.value.b, color.value.a));
    GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void OpenGLPainter::doBeginRender()
{
    FLUFFY_PROFILE_FUNCTION();
}

void OpenGLPainter::doEndRender()
{
    FLUFFY_PROFILE_FUNCTION();
}

void OpenGLPainter::doInitialize()
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glEnable(GL_BLEND));
    GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void OpenGLPainter::doTerminate()
{
    FLUFFY_PROFILE_FUNCTION();
}

void OpenGLPainter::drawIndexed(const Ref<VertexArray>& vertexArray, std::uint32_t indexCount)
{
    FLUFFY_PROFILE_FUNCTION();

    std::uint32_t count = (indexCount > 0) ? indexCount : (std::uint32_t)vertexArray->getIndexBuffer()->count();
    GlCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
}

void OpenGLPainter::setViewport(const FloatRect& relativeViewport, const RenderTarget& target)
{
    FLUFFY_PROFILE_FUNCTION();

    auto targetSize = target.getViewport();
    glViewport((GLint)(relativeViewport.left * targetSize.width),
               (GLint)(relativeViewport.top * targetSize.height),
               (GLsizei)(relativeViewport.width * targetSize.width),
               (GLsizei)(relativeViewport.height * targetSize.height));
}
