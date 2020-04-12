#pragma once

#include <fluffy/graphics/vertex.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class VertexArray
{
public:
    VertexArray() = default;
    VertexArray(std::size_t count);

    void                      resize(std::size_t count);
    [[nodiscard]] std::size_t getVerticesCount() const;
    [[nodiscard]] std::size_t getByteSize() const;

    void append(const Vertex& vertex);

    void clear();

    Vertex&       operator[](std::size_t index);
    const Vertex& operator[](std::size_t index) const;

    // @todo : temp function to return the vertices data, remove it when proper Drawable / Renderer classes in place
    float* raw() const
    {
        static float* vertices = nullptr;

        if (vertices) {
            delete[] vertices;
        }

        vertices = new float[getVerticesCount() * 8];

        for (int i = 0; i < (int)getVerticesCount(); ++i) {
            auto& v             = mVertices[i];
            vertices[i * 8]     = v.position.x;
            vertices[i * 8 + 1] = v.position.y;
            vertices[i * 8 + 2] = v.position.z;
            vertices[i * 8 + 3] = (v.color.r / 255.f);
            vertices[i * 8 + 4] = (v.color.g / 255.f);
            vertices[i * 8 + 5] = (v.color.b / 255.f);
            vertices[i * 8 + 6] = v.textureCoords.x;
            vertices[i * 8 + 7] = v.textureCoords.y;
        }

        return vertices;
    }

private:
    std::vector<Vertex> mVertices;
};
}
