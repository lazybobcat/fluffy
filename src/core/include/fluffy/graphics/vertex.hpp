#pragma once

#include <fluffy/graphics/color.hpp>
#include <fluffy/math/math.hpp>

#define FLUFFY_VERTEX_NB_ELEMENTS 9

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

    void                   setPosition(const Vector2f& position);
    void                   setPosition(const Vector3f& position);
    void                   setColor(const Color& color);
    void                   setTextureCoords(const Vector2f& textureCoords);
    [[nodiscard]] Vector3f getPosition() const;
    [[nodiscard]] Color    getColor() const;
    [[nodiscard]] Vector2f getTextureCoords() const;

    void setData(const Vector3f& position, const Color& color, const Vector2f& textureCoords);

    /**
     * data[0] = position.x
     * data[1] = position.y
     * data[2] = position.z
     * data[3] = color.r
     * data[4] = color.g
     * data[5] = color.b
     * data[6] = color.a
     * data[7] = textureCoords.x
     * data[8] = textureCoords.y
     */
    float data[FLUFFY_VERTEX_NB_ELEMENTS * sizeof(float)]{};
};
}
