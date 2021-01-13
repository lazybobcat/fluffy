#pragma once

#include <fluffy/graphics/renderer_api.hpp>

namespace Fluffy {

class OpenGLRendererAPI : public RendererAPI
{
public:
    void init() override;
    void setClearColor(const Color& color) override;
    void clear() override;
    void drawIndexed(const Ref<VertexArray>& vertexArray) override;
};
}