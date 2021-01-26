#pragma once

#include <fluffy/graphics/painter.hpp>

namespace Fluffy {

class OpenGLPainter : public Painter
{
public:
    OpenGLPainter()           = default;
    ~OpenGLPainter() override = default;

    void clear(const Color& color) override;

protected:
    void drawIndexed(const Ref<VertexArray>& vertexArray, std::uint32_t indexCount) override;
    void setViewport(const FloatRect& relativeViewport, const RenderTarget& target) override;

protected:
    void doInitialize() override;
    void doTerminate() override;

protected:
    void doBeginRender() override;
    void doEndRender() override;
};
}
