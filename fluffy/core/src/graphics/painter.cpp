#include <fluffy/graphics/painter.hpp>
#include <fluffy/graphics/render_context.hpp>
#include <fluffy/graphics/shape.hpp>
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

constexpr int MAX_TEXTURES_SLOTS_IN_SHADER = 32;

Fluffy::Color Painter::sClearColor = Color::Black;

void Painter::initialize(VideoModule* video)
{
    FLUFFY_PROFILE_FUNCTION();

    // Shaders @todo remove this from here and put it into Material
    mRenderingData.shader = Shader::create();
    mRenderingData.shader->loadFromFile("assets/shaders/sprite.vertex.shader", "assets/shaders/sprite.fragment.shader");
    mRenderingData.shader->enable();

    mRenderingData.quadVertexArray  = VertexArray::create();
    mRenderingData.quadVertexBuffer = VertexBuffer::create(mRenderingData.maxVertices * sizeof(Vertex));
    mRenderingData.quadVertexBuffer->setLayout({
      { ShaderDataType::Vector3f, "aPos" },
      { ShaderDataType::Vector2f, "aTexCoord" },
      { ShaderDataType::Vector4f, "aColor" },
      { ShaderDataType::Float, "aTexSlot" },
    });
    mRenderingData.quadVertexArray->addVertexBuffer(mRenderingData.quadVertexBuffer);

    mRenderingData.quadVertexBufferBase = new Vertex[mRenderingData.maxVertices];

    // @todo with multithread we might want to have a Ref<> on the indices instead because it might not be sent to the GPU right away
    auto*         quadIndices = new std::uint32_t[mRenderingData.maxIndices];
    std::uint32_t offset      = 0;
    for (std::uint32_t i = 0; i < mRenderingData.maxIndices; i += 6) {
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

    std::uint32_t white        = 0xffffffff;
    auto          blankTexture = Texture2D::create(1, 1);
    blankTexture->setRepeat(RepeatType::Repeat);
    blankTexture->setData(&white, sizeof(std::uint32_t));
    mRenderingData.textures.push_back(blankTexture);

    // Texture slots
    mRenderingData.maxTextureSlots = std::min(video->getMaxTextureSlots(), MAX_TEXTURES_SLOTS_IN_SHADER);
    int samplers[MAX_TEXTURES_SLOTS_IN_SHADER];
    for (int i = 0; i < mRenderingData.maxTextureSlots; ++i) {
        samplers[i] = i;
    }
    mRenderingData.shader->bindUniform("u_Textures", samplers, mRenderingData.maxTextureSlots);

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

    mActiveContext      = &context;
    mActiveCamera       = &context.getCamera();
    mActiveRenderTarget = &context.getDefaultRenderTarget();
    mActiveRenderTarget->onBind(*this);

    // @todo move this?
    mActiveCamera->updateProjection();
    setViewport(mActiveCamera->getViewport(), *mActiveRenderTarget);
    mRenderingData.shader->enable();
    mRenderingData.shader->bindUniform("u_ViewProjection", mActiveCamera->getViewProjection());
}

void Painter::unbind(RenderContext& context)
{
    FLUFFY_PROFILE_FUNCTION();

    flush();

    mActiveRenderTarget->onUnbind(*this);

    mActiveContext      = nullptr;
    mActiveCamera       = nullptr;
    mActiveRenderTarget = nullptr;
}

void Painter::beginRender()
{
    FLUFFY_PROFILE_FUNCTION();

    mRenderingData.quadVertexBufferPtr = mRenderingData.quadVertexBufferBase;

    // Reset pending draw
    clear(sClearColor);
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

    if (mActiveRenderTarget)
        mActiveRenderTarget->onStartDraw(*this);

    std::uint32_t dataSize = (uint32_t)((std::uint8_t*)mRenderingData.quadVertexBufferPtr - (std::uint8_t*)mRenderingData.quadVertexBufferBase);
    mRenderingData.quadVertexBuffer->setData(mRenderingData.quadVertexBufferBase, dataSize);

    if (dataSize > 0) {
        for (std::uint32_t i = 0; i < mRenderingData.textures.size(); ++i) {
            mRenderingData.textures[i]->bind(i);
        }
        mRenderingData.quadVertexArray->bind();
        drawIndexed(mRenderingData.quadVertexArray, mRenderingData.quadIndexCount);
        FLUFFY_PROFILE_DRAW_CALL(mRenderingData.quadVerticesCount, mRenderingData.quadIndexCount);
    }

    if (mActiveRenderTarget)
        mActiveRenderTarget->onEndDraw(*this);

    resetRenderingData();
}

void Painter::resetRenderingData()
{
    mRenderingData.quadVertexBufferPtr = mRenderingData.quadVertexBufferBase;
    mRenderingData.quadIndexCount      = 0;
    mRenderingData.quadVerticesCount   = 0;
    mRenderingData.textures.erase(++mRenderingData.textures.begin(), mRenderingData.textures.end()); // keep the first texture (blank)
}

void Painter::draw(const Ref<VertexArray>& vertexArray, std::uint32_t indexCount)
{
    vertexArray->bind();
    drawIndexed(vertexArray, indexCount);
    FLUFFY_PROFILE_DRAW_CALL(indexCount / 6 * 4, indexCount);
}

void Painter::draw(const VertexVector& vertices, const IndexBuffer& indices, const RenderStates& states)
{
    FLUFFY_PROFILE_FUNCTION();
}

void Painter::drawQuad(const VertexVector& vertices, const RenderStates& states)
{
    FLUFFY_PROFILE_FUNCTION();

    if (0 == vertices.getVerticesCount()) {
        return;
    }

    FLUFFY_ASSERT(4 == vertices.getVerticesCount(), "drawQuad only draws a quad, which have 4 vertices");

    if ((vertices.getVerticesCount() + mRenderingData.quadVerticesCount) > mRenderingData.maxVertices) {
        flush();
    }

    float textureIndex = 0.f;
    if (states.texture) {
        // check if texture is already in array
        for (int i = 1; i < mRenderingData.textures.size(); ++i) {
            if (states.texture->getAssetId() == mRenderingData.textures[i]->getAssetId()) {
                textureIndex = (float)i;
                break;
            }
        }

        // otherwise insert it
        if (textureIndex == 0.f) {
            if (mRenderingData.textures.size() >= mRenderingData.maxTextureSlots) {
                flush();
            }
            textureIndex = (float)mRenderingData.textures.size();
            mRenderingData.textures.push_back(states.texture);
        }
    }

    for (std::size_t i = 0; i < vertices.getVerticesCount(); ++i) {
        mRenderingData.quadVertexBufferPtr->position  = states.transform * Vector4f(vertices[i].position, 1.f);
        mRenderingData.quadVertexBufferPtr->color     = vertices[i].color;
        mRenderingData.quadVertexBufferPtr->texCoords = vertices[i].texCoords;
        mRenderingData.quadVertexBufferPtr->ts        = textureIndex;
        mRenderingData.quadVertexBufferPtr++;
    }

    mRenderingData.quadIndexCount += 6;
    mRenderingData.quadVerticesCount += (std::uint32_t)vertices.getVerticesCount();
}

void Painter::drawShape(Shape& shape, const RenderStates& states)
{
    shape.draw(*this, states);
}

void Painter::setClearColor(const Color& color)
{
    sClearColor = color;
}
