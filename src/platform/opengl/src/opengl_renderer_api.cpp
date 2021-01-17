#include "opengl_renderer_api.hpp"
#include "opengl.hpp"
#include <fluffy/graphics/render_command.hpp>
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

RendererAPI* RenderCommand::mRendererAPI = new OpenGLRendererAPI();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OpenGLRendererAPI::initialize()
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glEnable(GL_BLEND));
    GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void OpenGLRendererAPI::terminate()
{
    FLUFFY_PROFILE_FUNCTION();
}

void OpenGLRendererAPI::setClearColor(const Color& color)
{
    glClearColor(color.value.r, color.value.g, color.value.b, color.value.a);
}

void OpenGLRendererAPI::clear()
{
    FLUFFY_PROFILE_FUNCTION();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vertexArray)
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr));
}
