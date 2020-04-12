#include <fluffy/graphics/vertex.hpp>

using namespace Fluffy;

Vertex::Vertex()
  : position(0, 0, 0)
  , color(Color::Black)
  , textureCoords(0, 0)
{
}

Vertex::Vertex(const Vector2f& position)
  : position(position.x, position.y, 0)
  , color(Color::Black)
  , textureCoords(0, 0)
{
}

Vertex::Vertex(const Vector3f& position)
  : position(position)
  , color(Color::Black)
  , textureCoords(0, 0)
{
}

Vertex::Vertex(const Vector2f& position, const Color& color)
  : position(position.x, position.y, 0)
  , color(color)
  , textureCoords(0, 0)
{
}

Vertex::Vertex(const Vector3f& position, const Color& color)
  : position(position)
  , color(color)
  , textureCoords(0, 0)
{
}

Vertex::Vertex(const Vector2f& position, const Vector2f& textureCoords)
  : position(position.x, position.y, 0)
  , color(Color::Black)
  , textureCoords(textureCoords)
{
}

Vertex::Vertex(const Vector3f& position, const Vector2f& textureCoords)
  : position(position)
  , color(Color::Black)
  , textureCoords(textureCoords)
{
}

Vertex::Vertex(const Vector2f& position, const Color& color, const Vector2f& textureCoords)
  : position(position.x, position.y, 0)
  , color(color)
  , textureCoords(textureCoords)
{
}

Vertex::Vertex(const Vector3f& position, const Color& color, const Vector2f& textureCoords)
  : position(position)
  , color(color)
  , textureCoords(textureCoords)
{
}
