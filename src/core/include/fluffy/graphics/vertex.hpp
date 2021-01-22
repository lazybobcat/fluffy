#pragma once

#include <fluffy/graphics/color.hpp>
#include <fluffy/graphics/shader.hpp>
#include <fluffy/math/math.hpp>
#include <fluffy/math/rectangle.hpp>

namespace Fluffy {

//enum PrimitiveType
//{
//    Points        = 0,
//    Lines         = 1,
//    LineLoop      = 2,
//    LineStrip     = 3,
//    Triangles     = 4,
//    TriangleStrip = 5,
//    TriangleFan   = 6,
//};

struct Vertex
{
    Vertex() = default;
    explicit Vertex(const Vector3f& position);
    explicit Vertex(const Vector3f& position, const Color& color);
    explicit Vertex(const Vector3f& position, const Color& color, const Vector2f& texCoords);

    Vector3f position  = Vector3f(0.f, 0.f, 0.f);
    Vector2f texCoords = Vector2f(0.f, 0.f);
    Color    color     = Color::White;
    float    ts        = 0.f; // texture slot
};

class VertexVector
{
public:
    VertexVector();
    explicit VertexVector(std::size_t count);

    void append(const Vertex& vertex);
    void clear();
    void resize(std::size_t count);

    std::size_t getVerticesCount() const;
    FloatRect   getBounds() const;

    Vertex&       operator[](std::size_t index);
    const Vertex& operator[](std::size_t index) const;

private:
    std::vector<Vertex> mVertices;
};
}