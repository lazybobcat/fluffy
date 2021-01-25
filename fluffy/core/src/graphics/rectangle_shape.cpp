#include <fluffy/graphics/rectangle_shape.hpp>

using namespace Fluffy;

RectangleShape::RectangleShape(const Vector2f& size)
  : mSize(size)
{
    setOrigin({ 0.5f, 0.5f, 0.f });
    update();
}

void RectangleShape::setSize(const Vector2f& size)
{
    mSize = size;
    update();
}

Vector2f RectangleShape::getSize() const
{
    return mSize;
}

Vector3f RectangleShape::getVertexPosition(std::size_t index)
{
    auto origin = getOrigin();

    switch (index) {
        case 0:
            return { 0.f - origin.x * mSize.x, 0.f - origin.y * mSize.y, 0.f };
        case 1:
            return { mSize.x - origin.x * mSize.x, 0.f - origin.y * mSize.y, 0.f };
        case 2:
            return { mSize.x - origin.x * mSize.x, mSize.y - origin.y * mSize.y, 0.f };
        case 3:
            return { 0.f - origin.x * mSize.x, mSize.y - origin.y * mSize.y, 0.f };
    }

    return { 0.f, 0.f, 0.f };
}