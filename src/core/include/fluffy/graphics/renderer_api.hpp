#pragma once

#include <fluffy/graphics/color.hpp>
#include <fluffy/graphics/vertex.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class RendererAPI
{
public:
    virtual void setClearColor(const Color& color = Color::Magenta) = 0;
    virtual void clear()                                            = 0;
    virtual void drawIndexed(const Ref<VertexArray>& vertexArray)   = 0;
};
}
