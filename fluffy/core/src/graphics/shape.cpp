#include <fluffy/graphics/painter.hpp>
#include <fluffy/graphics/shape.hpp>

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

    return transformRect(transform, bounds);
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
    painter.drawQuad(mVertices, states);
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

const VertexVector& Shape::getVertices() const
{
    return mVertices;
}
