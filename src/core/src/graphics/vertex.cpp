#include <fluffy/graphics/vertex.hpp>

using namespace Fluffy;

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
  : mElements(elements)
{
    calculateOffsetAndStride();
}

void BufferLayout::calculateOffsetAndStride()
{
    std::uint64_t offset = 0;
    mStride              = 0;
    for (auto& element : mElements) {
        element.offset = offset;
        offset += element.size;
        mStride += element.size;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vertex::Vertex()
{
    setData({ 0, 0, 0 }, Color::Black, { 0, 0 });
}

Vertex::Vertex(const Vector2f& position)
{
    setData({ position.x, position.y, 0 }, Color::Black, { 0, 0 });
}

Vertex::Vertex(const Vector3f& position)
{
    setData(position, Color::Black, { 0, 0 });
}

Vertex::Vertex(const Vector2f& position, const Color& color)
{
    setData({ position.x, position.y, 0 }, color, { 0, 0 });
}

Vertex::Vertex(const Vector3f& position, const Color& color)
{
    setData(position, color, { 0, 0 });
}

Vertex::Vertex(const Vector2f& position, const Vector2f& textureCoords)
{
    setData({ position.x, position.y, 0 }, Color::Black, textureCoords);
}

Vertex::Vertex(const Vector3f& position, const Vector2f& textureCoords)
{
    setData(position, Color::Black, textureCoords);
}

Vertex::Vertex(const Vector2f& position, const Color& color, const Vector2f& textureCoords)
{
    setData({ position.x, position.y, 0 }, color, textureCoords);
}

Vertex::Vertex(const Vector3f& position, const Color& color, const Vector2f& textureCoords)
{
    setData(position, color, textureCoords);
}

void Vertex::setData(const Vector3f& position, const Color& color, const Vector2f& textureCoords)
{
    setPosition(position);
    setColor(color);
    setTextureCoords(textureCoords);
}

void Vertex::setPosition(const Vector2f& position)
{
    data[0] = position.x;
    data[1] = position.y;
    data[2] = 0.f;
}

void Vertex::setPosition(const Vector3f& position)
{
    data[0] = position.x;
    data[1] = position.y;
    data[2] = position.z;
}

void Vertex::setColor(const Color& color)
{
    data[3] = color.r / 255.f;
    data[4] = color.g / 255.f;
    data[5] = color.b / 255.f;
    data[6] = color.a / 255.f;
}

void Vertex::setTextureCoords(const Vector2f& textureCoords)
{
    data[7] = textureCoords.x;
    data[8] = textureCoords.y;
}

Vector3f Vertex::getPosition() const
{
    return Fluffy::Vector3f(data[0], data[1], data[2]);
}

Color Vertex::getColor() const
{
    return Color(data[3], data[4], data[5], data[6]);
}

Vector2f Vertex::getTextureCoords() const
{
    return Fluffy::Vector2f(data[7], data[8]);
}
