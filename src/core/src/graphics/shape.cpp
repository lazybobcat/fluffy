#include <fluffy/graphics/shape.hpp>
#include <fluffy/graphics/painter.hpp>

using namespace Fluffy;

Shape::Shape()
  : mVertices()
  , mOutlineVertices()
{
}

void Shape::setFillColor(const Color& color)
{
    mFillColor = color;
    updateFillColors();
}

const Color& Shape::getFillColor() const
{
    return mFillColor;
}

void Shape::setOutlineColor(const Color& color)
{
    mOutlineColor = color;
    updateOutlineColors();
}

const Color& Shape::getOutlineColor() const
{
    return mOutlineColor;
}

void Shape::setOutlineThickness(float thickness)
{
    mOutlineThickness = thickness;
    update();
}

float Shape::getOutlineThickness() const
{
    return mOutlineThickness;
}

FloatRect Shape::getLocalBounds() const
{
    return mBounds;
}

FloatRect Shape::getGlobalBounds() const
{
    auto transform = getTransformMatrix();
    auto bounds    = getLocalBounds();

    // Transform the bounding rectangle 4 corners
    const Vector4f points[] = {
        transform * Vector4f(bounds.left, bounds.top, 1.f, 1.f),                               // top-left corner
        transform * Vector4f(bounds.left, bounds.top + bounds.height, 1.f, 1.f),               // bottom-left corner
        transform * Vector4f(bounds.left + bounds.width, bounds.top, 1.f, 1.f),                // top-right corner
        transform * Vector4f(bounds.left + bounds.width, bounds.top + bounds.height, 1.f, 1.f) // bottom-right corner
    };

    // Compute the transformed bounding rectangle
    float left   = points[0].x;
    float top    = points[0].y;
    float right  = points[0].x;
    float bottom = points[0].y;
    for (int i = 1; i < 4; ++i) {
        if (points[i].x < left)
            left = points[i].x;
        else if (points[i].x > right)
            right = points[i].x;
        if (points[i].y < top)
            top = points[i].y;
        else if (points[i].y > bottom)
            bottom = points[i].y;
    }

    return FloatRect(left, top, right - left, bottom - top);
}

void Shape::update()
{
    std::size_t count = getVerticesCount();

    // If 2 or less vertices, we can't do anything
    if (count < 3) {
        mVertices.resize(0);
        mOutlineVertices.resize(0);

        return;
    }

    mVertices.resize(count);

    for (std::size_t i = 0; i < count; ++i) {
        mVertices[i].position = getVertexPosition(i);
    }

    mInsideBounds = mVertices.getBounds();

    updateFillColors();
    updateOutline();
}

void Shape::draw(Painter& painter, RenderStates states) const
{
    states.transform *= getTransformMatrix();
    painter.drawQuads(mVertices, states);
}

void Shape::updateFillColors()
{
    for (std::size_t i = 0; i < mVertices.getVerticesCount(); ++i) {
        mVertices[i].color = mFillColor;
    }
}

void Shape::updateOutlineColors()
{
    for (std::size_t i = 0; i < mOutlineVertices.getVerticesCount(); ++i) {
        mOutlineVertices[i].color = mFillColor;
    }
}

void Shape::updateOutline()
{
    // @todo compute outline vertices

    updateOutlineColors();
    mBounds = mOutlineVertices.getBounds();
}
