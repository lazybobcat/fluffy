#include "opengl_renderer_api.hpp"
#include "opengl.hpp"
#include <fluffy/graphics/render_command.hpp>

using namespace Fluffy;

RendererAPI* RenderCommand::mRendererAPI = new OpenGLRendererAPI();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OpenGLRendererAPI::init()
{
    GlCall(glEnable(GL_BLEND));
    GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void OpenGLRendererAPI::setClearColor(const Color& color)
{
    glClearColor(color.value.r, color.value.g, color.value.b, color.value.a);
}

void OpenGLRendererAPI::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vertexArray)
{
    GlCall(glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr));
}
