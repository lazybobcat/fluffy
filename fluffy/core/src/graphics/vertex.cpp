#include <fluffy/graphics/vertex.hpp>

using namespace Fluffy;

Vertex::Vertex(const Vector3f& position)
  : position(position)
{
}

Vertex::Vertex(const Vector3f& position, const Color& color)
  : position(position)
  , color(color)
{
}

Vertex::Vertex(const Vector3f& position, const Color& color, const Vector2f& texCoords)
  : position(position)
  , color(color)
  , texCoords(texCoords)
{
}

/**********************************************************************************************************************/

VertexVector::VertexVector()
  : mVertices()
{
}

VertexVector::VertexVector(std::size_t count)
  : mVertices(count)
{
}

void VertexVector::append(const Vertex& vertex)
{
    mVertices.push_back(vertex);
}

void VertexVector::clear()
{
    mVertices.clear();
}

void VertexVector::resize(std::size_t count)
{
    mVertices.resize(count);
}

std::size_t VertexVector::getVerticesCount() const
{
    return mVertices.size();
}

FloatRect VertexVector::getBounds() const
{
    if (!mVertices.empty()) {
        float left   = mVertices[0].position.x;
        float top    = mVertices[0].position.y;
        float right  = mVertices[0].position.x;
        float bottom = mVertices[0].position.y;

        for (std::size_t i = 1; i < mVertices.size(); ++i) {
            Vector2f position = mVertices[i].position;

            // Update left and right
            if (position.x < left) {
                left = position.x;
            } else if (position.x > right) {
                right = position.x;
            }

            // Update top and bottom
            if (position.y < top) {
                top = position.y;
            } else if (position.y > bottom) {
                bottom = position.y;
            }
        }

        return FloatRect(left, top, right - left, bottom - top);
    }

    return FloatRect();
}

Vertex& VertexVector::operator[](std::size_t index)
{
    return mVertices[index];
}

const Vertex& VertexVector::operator[](std::size_t index) const
{
    return mVertices[index];
}
