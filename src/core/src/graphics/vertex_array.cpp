#include <fluffy/graphics/vertex_array.hpp>
#include <glad/glad.h>

using namespace std;

Fluffy::VertexArray::VertexArray()
{
    glGenVertexArrays(1, &mId);
}

Fluffy::VertexArray::VertexArray(std::size_t count)
  : mVertices(count)
{
    glGenVertexArrays(1, &mId);
}

Fluffy::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &mId);
}

void Fluffy::VertexArray::resize(std::size_t count)
{
    mVertices.resize(count);
}

std::size_t Fluffy::VertexArray::getVerticesCount() const
{
    return mVertices.size();
}

std::size_t Fluffy::VertexArray::getByteSize() const
{
    return getVerticesCount() * FLUFFY_VERTEX_NB_ELEMENTS * sizeof(float);
}

void Fluffy::VertexArray::append(const Fluffy::Vertex& vertex)
{
    mVertices.push_back(vertex);
}

void Fluffy::VertexArray::clear()
{
    mVertices.clear();
}

Fluffy::Vertex& Fluffy::VertexArray::operator[](std::size_t index)
{
    return mVertices[index];
}

const Fluffy::Vertex& Fluffy::VertexArray::operator[](std::size_t index) const
{
    return mVertices[index];
}

void Fluffy::VertexArray::bind()
{
    glBindVertexArray(mId);
}
