#include <fluffy/graphics/render_command.hpp>
#include <fluffy/graphics/renderer.hpp>

using namespace Fluffy;

Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData();

void Renderer::initialize()
{
    RenderCommand::init();
}

void Renderer::terminate()
{
    RenderCommand::terminate();
}

void Renderer::beginScene(const Camera& camera)
{
    RenderCommand::clear();
    mSceneData->viewProjectionMatrix = camera.getViewProjection();
}

void Renderer::endScene()
{
}

void Renderer::draw(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
{
    shader->enable();
    shader->bindUniform("u_ViewProjection", mSceneData->viewProjectionMatrix);
    shader->bindUniform("u_Transform", transform);

    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);

    shader->disable();
}

/**********************************************************************************************************************/

struct Renderer2DData
{
    Ref<VertexArray> vertexArray;
    Ref<Shader>      shader;
    Ref<Texture2D>   blankTexture;
};

static Renderer2DData* RenderingData;

void Renderer2D::initialize()
{
    RenderingData = new Renderer2DData();

    // Shaders
    RenderingData->shader = Shader::create();
    RenderingData->shader->loadFromFile("assets/shaders/sprite.vertex.shader", "assets/shaders/sprite.fragment.shader");
    RenderingData->shader->enable();
    RenderingData->shader->bindUniform("spriteTexture", 0);

    RenderingData->vertexArray  = VertexArray::create();
    float verticesSquare[4 * 5] = {
        1.f, -1.f, 0.0f, 1.f, 0.f,
        1.f, 1.f, 0.0f, 1.f, 1.f,
        -1.f, -1.f, 0.0f, 0.f, 0.f,
        -1.f, 1.f, 0.0f, 0.f, 1.f
    };
    Ref<VertexBuffer> vbSquare = VertexBuffer::create(verticesSquare, sizeof(verticesSquare));
    vbSquare->setLayout({
      { ShaderDataType::Vector3f, "aPos" },
      { ShaderDataType::Vector2f, "aTexCoord" },
    });
    std::uint32_t    indicesSquare[6] = { 0, 1, 2, 2, 3, 1 };
    Ref<IndexBuffer> ibSquare         = IndexBuffer::create(indicesSquare, 6);
    RenderingData->vertexArray->addVertexBuffer(vbSquare);
    RenderingData->vertexArray->setIndexBuffer(ibSquare);

    std::uint32_t white = 0xffffffff;
    RenderingData->blankTexture = Texture2D::create(1, 1);
    RenderingData->blankTexture->setRepeat(RepeatType::Repeat);
    RenderingData->blankTexture->setData(&white, sizeof(std::uint32_t));
}

void Renderer2D::terminate()
{
    delete RenderingData;
}

void Renderer2D::beginScene(const Camera& camera)
{
    RenderCommand::clear();

    RenderingData->shader->enable();
    RenderingData->shader->bindUniform("u_ViewProjection", camera.getViewProjection());
}

void Renderer2D::endScene()
{
}

void Renderer2D::drawQuad(const Color& color, const glm::mat4& transform)
{
    RenderingData->shader->bindUniform("u_Transform", transform);
    RenderingData->shader->bindUniform("u_Color", color);

    RenderingData->blankTexture->bind();

    RenderingData->vertexArray->bind();
    RenderCommand::drawIndexed(RenderingData->vertexArray);

    RenderingData->blankTexture->unbind();
}

void Renderer2D::drawQuad(const Ref<Texture2D>& texture, const Color& color, const glm::mat4& transform)
{
    RenderingData->shader->bindUniform("u_Transform", transform);
    RenderingData->shader->bindUniform("u_Color", color);

    texture->bind();

    RenderingData->vertexArray->bind();
    RenderCommand::drawIndexed(RenderingData->vertexArray);

    texture->unbind();
}
