#pragma once

#include <fluffy/graphics/vertex.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class VertexArray
{
public:
    VertexArray();
    explicit VertexArray(std::size_t count); // @todo primitive type
    ~VertexArray();

    void                      resize(std::size_t count);
    [[nodiscard]] std::size_t getVerticesCount() const;
    [[nodiscard]] std::size_t getByteSize() const;

    void append(const Vertex& vertex);

    void clear();

    Vertex&       operator[](std::size_t index);
    const Vertex& operator[](std::size_t index) const;

    void bind();

    // @todo : temp function to return the vertices data, remove it when proper Drawable / Renderer classes in place
    const float* raw() const
    {
        static float* vertices = nullptr;

        if (vertices) {
            delete[] vertices;
        }

        vertices = new float[getVerticesCount() * FLUFFY_VERTEX_NB_ELEMENTS];

        for (int i = 0; i < (int)getVerticesCount(); ++i) {
            auto& v             = mVertices[i];
            vertices[i * 8]     = v.position.x;
            vertices[i * 8 + 1] = v.position.y;
            vertices[i * 8 + 2] = v.position.z;
            vertices[i * 8 + 3] = (v.color.r / 255.f);
            vertices[i * 8 + 4] = (v.color.g / 255.f);
            vertices[i * 8 + 5] = (v.color.b / 255.f);
            vertices[i * 8 + 6] = (v.color.a / 255.f);
            vertices[i * 8 + 7] = v.textureCoords.x;
            vertices[i * 8 + 8] = v.textureCoords.y;
        }

        return vertices;
    }

private:
    unsigned int        mId;
    std::vector<Vertex> mVertices;
};
}
