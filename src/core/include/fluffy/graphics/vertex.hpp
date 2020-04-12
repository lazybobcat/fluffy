#pragma once

#include <fluffy/graphics/color.hpp>
#include <fluffy/math/math.hpp>

namespace Fluffy {

struct Vertex
{
    Vertex();
    explicit Vertex(const Vector2f& position); // default Z = 0
    explicit Vertex(const Vector3f& position);
    Vertex(const Vector2f& position, const Color& color);
    Vertex(const Vector3f& position, const Color& color);
    Vertex(const Vector2f& position, const Vector2f& textureCoords);
    Vertex(const Vector3f& position, const Vector2f& textureCoords);
    Vertex(const Vector2f& position, const Color& color, const Vector2f& textureCoords);
    Vertex(const Vector3f& position, const Color& color, const Vector2f& textureCoords);

    Vector3f position;
    Color    color;
    Vector2f textureCoords;
};

#define FLUFFY_VERTEX_NB_ELEMENTS 9
}
