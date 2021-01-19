#include <fluffy/graphics/painter.hpp>
#include <fluffy/graphics/render_context.hpp>
#include <fluffy/profiling/profiler.hpp>
#include <fluffy/graphics/shape.hpp>

using namespace Fluffy;

void Painter::initialize()
{
    FLUFFY_PROFILE_FUNCTION();

    // Shaders @todo remove this from here and put it into Material
    mRenderingData.shader = Shader::create();
    mRenderingData.shader->loadFromFile("assets/shaders/sprite.vertex.shader", "assets/shaders/sprite.fragment.shader");
    mRenderingData.shader->enable();
    mRenderingData.shader->bindUniform("spriteTexture", 0);

    mRenderingData.quadVertexArray = VertexArray::create();
    mRenderingData.quadVertexBuffer = VertexBuffer::create(mRenderingData.maxVertices * sizeof(Vertex));
    mRenderingData.quadVertexBuffer->setLayout({
                                                 { ShaderDataType::Vector3f, "aPos" },
                                                 { ShaderDataType::Vector2f, "aTexCoord" },
                                                 { ShaderDataType::Vector4f, "aColor" },
                                               });
    mRenderingData.quadVertexArray->addVertexBuffer(mRenderingData.quadVertexBuffer);

    mRenderingData.quadVertexBufferBase = new Vertex[mRenderingData.maxVertices];

    // @todo with multithread we might want to have a Ref<> on the indices instead because it might not be sent to the GPU right away
    auto* quadIndices = new std::uint32_t[mRenderingData.maxIndices];
    std::uint32_t offset = 0;
    for (std::uint32_t i = 0; i < mRenderingData.maxIndices; i+= 6) {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;
        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += 4;
    }

    Ref<IndexBuffer> ibSquare = IndexBuffer::create(quadIndices, mRenderingData.maxIndices);
    mRenderingData.quadVertexArray->setIndexBuffer(ibSquare);
    delete[] quadIndices;

    std::uint32_t white = 0xffffffff;
    mRenderingData.blankTexture = Texture2D::create(1, 1);
    mRenderingData.blankTexture->setRepeat(RepeatType::Repeat);
    mRenderingData.blankTexture->setData(&white, sizeof(std::uint32_t));

    doInitialize();
}

void Painter::terminate()
{
    FLUFFY_PROFILE_FUNCTION();

    delete[] mRenderingData.quadVertexBufferBase;
    doTerminate();

}

void Painter::bind(RenderContext& context)
{
    FLUFFY_PROFILE_FUNCTION();

    mActiveContext = &context;
    mActiveCamera = &context.getCamera();
    mActiveRenderTarget = &context.getDefaultRenderTarget();

    // @todo move this?
    mRenderingData.shader->enable();
    mRenderingData.shader->bindUniform("u_ViewProjection", mActiveCamera->getViewProjection());
}

void Painter::unbind(RenderContext& context)
{
    FLUFFY_PROFILE_FUNCTION();

    flush();

    mActiveContext = nullptr;
    mActiveCamera = nullptr;
    mActiveRenderTarget = nullptr;
}

void Painter::beginRender()
{
    FLUFFY_PROFILE_FUNCTION();
    // @todo stats

    mRenderingData.quadVertexBufferPtr = mRenderingData.quadVertexBufferBase;
    mRenderingData.quadIndexCount = 0;

    // Reset pending draw
    doBeginRender();
}

void Painter::endRender()
{
    FLUFFY_PROFILE_FUNCTION();

    flush();
    doEndRender();
    mActiveCamera = nullptr;
}

void Painter::flush()
{
    FLUFFY_PROFILE_FUNCTION();

    std::uint32_t dataSize = (std::uint8_t*)mRenderingData.quadVertexBufferPtr - (std::uint8_t*)mRenderingData.quadVertexBufferBase;
    mRenderingData.quadVertexBuffer->setData(mRenderingData.quadVertexBufferBase, dataSize);

    if (dataSize > 0) {
        mRenderingData.blankTexture->bind(); // @todo remove this ASAP this is just for testing, should be part of Material
        drawIndexed(mRenderingData.quadVertexArray, mRenderingData.quadIndexCount);
        mRenderingData.blankTexture->unbind();// @todo same
    }

    // @todo move into another method resetPending()?
    mRenderingData.quadVertexBufferPtr = mRenderingData.quadVertexBufferBase;
}

void Painter::draw(const VertexVector& vertices, const IndexBuffer& indices, const RenderStates& states)
{
    FLUFFY_PROFILE_FUNCTION();
}

void Painter::drawQuads(const VertexVector& vertices, const RenderStates& states)
{
    FLUFFY_PROFILE_FUNCTION();

    if (0 == vertices.getVerticesCount()) {
        return;
    }

    for (std::size_t i = 0; i < vertices.getVerticesCount(); ++i) {
        mRenderingData.quadVertexBufferPtr->position = states.transform * Vector4f(vertices[i].position, 1.f);
        mRenderingData.quadVertexBufferPtr->color = vertices[i].color;
        mRenderingData.quadVertexBufferPtr->texCoords = vertices[i].texCoords;
        mRenderingData.quadVertexBufferPtr++;
    }

    mRenderingData.quadIndexCount += 6;
}

void Painter::drawShape(Shape& shape, const RenderStates& states)
{
    shape.draw(*this, states);
}
