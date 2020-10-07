#include "opengl_renderer_api.hpp"
#include "opengl.hpp"
#include <fluffy/graphics/render_command.hpp>

using namespace Fluffy;

RendererAPI* RenderCommand::mRendererAPI = new OpenGLRendererAPI();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OpenGLRendererAPI::setClearColor(const Color& color)
{
    float red, green, blue, alpha = 0;
    color.getFloatValues(&red, &green, &blue, &alpha);
    glClearColor(red, green, blue, alpha);
}

void OpenGLRendererAPI::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vertexArray)
{
    GlCall(glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr));
}
