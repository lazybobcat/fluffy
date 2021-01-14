#pragma once

#include <fluffy/graphics/renderer_api.hpp>

namespace Fluffy {

class RenderCommand
{
public:
    inline static void init()
    {
        mRendererAPI->initialize();
    }

    inline static void terminate()
    {
        mRendererAPI->terminate();
    }

    inline static void setClearColor(const Color& color = Color::Magenta)
    {
        mRendererAPI->setClearColor(color);
    }

    inline static void clear()
    {
        mRendererAPI->clear();
    }

    inline static void drawIndexed(const Ref<VertexArray>& vertexArray)
    {
        mRendererAPI->drawIndexed(vertexArray);
    }

private:
    static RendererAPI* mRendererAPI;
};
}
