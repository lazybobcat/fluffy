#pragma once

#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/color.hpp>
#include <fluffy/graphics/render_states.hpp>
#include <fluffy/graphics/vertex.hpp>
#include <fluffy/graphics/vertex_buffers.hpp>

namespace Fluffy {

class Camera;
class Game;
class RenderContext;
class RenderTarget;
class Shape;

struct PainterData
{
    const std::uint32_t maxQuads        = 1000;
    const std::uint32_t maxVertices     = maxQuads * 4;
    const std::uint32_t maxIndices      = maxQuads * 6;
    int                 maxTextureSlots = 2;

    Ref<VertexArray>            quadVertexArray;
    Ref<VertexBuffer>           quadVertexBuffer;
    Ref<Shader>                 shader;
    std::vector<Ref<Texture2D>> textures;

    std::uint32_t quadIndexCount       = 0;
    std::uint32_t quadVerticesCount    = 0;
    Vertex*       quadVertexBufferBase = nullptr;
    Vertex*       quadVertexBufferPtr  = nullptr;
};

class Painter
{
public:
    virtual ~Painter() = default;

    virtual void clear(const Color& color) = 0;

    void flush();

    // Draw methods
    void draw(const Ref<VertexArray>& vertexArray, std::uint32_t indexCount /*, Ref<Material> material*/);                        // Assumes that the primitive type is always TRIANGLES
    void draw(const VertexVector& vertices, const IndexBuffer& indices /*, Ref<Material> material*/, const RenderStates& states); // Assumes that the primitive type is always TRIANGLES
    void drawQuad(const VertexVector& vertices /*, Ref<Material> material*/, const RenderStates& states);
    // void drawSprite(...); // @todo
    void drawLine(const std::vector<Vector2f>& points, const Color& color, float thickness /*, Ref<Material> material*/);
    void drawRectangle();
    // void drawCircle(...); // @todo
    void drawShape(Shape& shape, const RenderStates& states); // calls the Shape.draw() method. Shape is in charge of calling the Painter's base draw methods.

private:
    friend class RenderContext;
    friend class Game;

    void initialize(VideoModule* video);
    void terminate();

    void bind(RenderContext& context);
    void unbind(RenderContext& context);

    void beginRender();
    void endRender();

    void resetRenderingData();

protected:
    Painter() = default;

    virtual void doInitialize()  = 0;
    virtual void doTerminate()   = 0;
    virtual void doBeginRender() = 0;
    virtual void doEndRender()   = 0;

    virtual void drawIndexed(const Ref<VertexArray>& vertexArray, std::uint32_t indexCount) = 0;

private:
    PainterData mRenderingData;

    RenderContext* mActiveContext      = nullptr;
    RenderTarget*  mActiveRenderTarget = nullptr;
    Camera*        mActiveCamera       = nullptr;
};
}