#include <fluffy/graphics/rectangle_shape.hpp>

using namespace Fluffy;

RectangleShape::RectangleShape(const Vector2f& size)
  : mSize(size)
{
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
    auto scale = getScale();

    switch (index) {
        case 0:
            return { - scale.x * mSize.x / 2.f, - scale.y * mSize.y / 2.f, 0.f };
        case 1:
            return { scale.x * mSize.x / 2.f, - scale.y * mSize.y / 2.f, 0.f };
        case 2:
            return { scale.x * mSize.x / 2.f, scale.y * mSize.y / 2.f, 0.f };
        case 3:
            return { - scale.x * mSize.x /2.f, scale.y * mSize.y / 2.f, 0.f };
    }

    return { 0.f, 0.f, 0.f };
}