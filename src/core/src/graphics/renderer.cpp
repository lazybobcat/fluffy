#include <fluffy/graphics/render_command.hpp>
#include <fluffy/graphics/renderer.hpp>

using namespace Fluffy;

Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData();

void Renderer::beginScene(const Camera& camera)
{
    mSceneData->viewProjectionMatrix = camera.getViewProjection();
}

void Renderer::endScene()
{
}

void Renderer::draw(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader)
{
    shader->enable();
    shader->bindUniform("u_ViewProjection", mSceneData->viewProjectionMatrix);
    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
    shader->disable();
}
