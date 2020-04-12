#include <fluffy/graphics/vertex_array.hpp>

using namespace std;

Fluffy::VertexArray::VertexArray()
  : mVerticesData()
  , mPrimitiveType(PrimitiveType::Points)
{
    glGenVertexArrays(1, &mId);
}

Fluffy::VertexArray::VertexArray(PrimitiveType type, std::size_t count)
  : mVerticesData(count * FLUFFY_VERTEX_NB_ELEMENTS)
  , mPrimitiveType(type)
{
    glGenVertexArrays(1, &mId);
}

Fluffy::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &mId);
}

void Fluffy::VertexArray::resize(std::size_t count)
{
    mVerticesData.resize(count * FLUFFY_VERTEX_NB_ELEMENTS);
}

std::size_t Fluffy::VertexArray::getVerticesCount() const
{
    return mVerticesData.size() / FLUFFY_VERTEX_NB_ELEMENTS;
}

std::size_t Fluffy::VertexArray::getByteSize() const
{
    return mVerticesData.size() * sizeof(float);
}

void Fluffy::VertexArray::append(const Fluffy::Vertex& vertex)
{
    mVerticesData.insert(mVerticesData.end(), vertex.data, vertex.data + FLUFFY_VERTEX_NB_ELEMENTS);
}

void Fluffy::VertexArray::setVertex(std::size_t position, const Fluffy::Vertex& vertex)
{
    mVerticesData[position * FLUFFY_VERTEX_NB_ELEMENTS + 0] = vertex.data[0];
    mVerticesData[position * FLUFFY_VERTEX_NB_ELEMENTS + 1] = vertex.data[1];
    mVerticesData[position * FLUFFY_VERTEX_NB_ELEMENTS + 2] = vertex.data[2];
    mVerticesData[position * FLUFFY_VERTEX_NB_ELEMENTS + 3] = vertex.data[3];
    mVerticesData[position * FLUFFY_VERTEX_NB_ELEMENTS + 4] = vertex.data[4];
    mVerticesData[position * FLUFFY_VERTEX_NB_ELEMENTS + 5] = vertex.data[5];
    mVerticesData[position * FLUFFY_VERTEX_NB_ELEMENTS + 6] = vertex.data[6];
    mVerticesData[position * FLUFFY_VERTEX_NB_ELEMENTS + 7] = vertex.data[7];
    mVerticesData[position * FLUFFY_VERTEX_NB_ELEMENTS + 8] = vertex.data[8];
}

void Fluffy::VertexArray::clear()
{
    mVerticesData.clear();
}

void Fluffy::VertexArray::bind()
{
    glBindVertexArray(mId);
}
