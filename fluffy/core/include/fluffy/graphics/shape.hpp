#pragma once

#include <fluffy/graphics/color.hpp>
#include <fluffy/graphics/drawable.hpp>
#include <fluffy/graphics/transformable.hpp>
#include <fluffy/graphics/vertex.hpp>
#include <fluffy/math/rectangle.hpp>

namespace Fluffy {

class Shape : public Transformable
  , public Drawable
{
public:
    virtual ~Shape() = default;

    /**
     * Number of vertices of the shape
     */
    virtual std::size_t getVerticesCount() = 0;

    /**
     * Get the shape local coordinates of the vertex (transformations not taken into account)
     */
    virtual Vector3f getVertexPosition(std::size_t index) = 0;

    virtual void setFillColor(const Color& color);
    void         setOutlineColor(const Color& color);
    void         setOutlineThickness(float thickness);

    const Color& getFillColor() const;
    const Color& getOutlineColor() const;
    float        getOutlineThickness() const;

    /**
     * Get the local bounding rect (transformations not taken into account)
     */
    FloatRect getLocalBounds() const;

    /**
     * Get the bounding rect in global (world) coordinates
     */
    FloatRect getGlobalBounds() const;

    const VertexVector& getVertices() const;

protected:
    Shape();

    /**
     * Recompute the shape geometry
     */
    void update();

private:
    friend class Painter;

    void draw(Painter& painter, RenderStates states) const override;

    void updateFillColors();
    void updateOutlineColors();
    void updateOutline();

private:
    VertexVector mVertices;
    VertexVector mOutlineVertices;
    Color        mFillColor        = Color::White;
    Color        mOutlineColor     = Color::White;
    float        mOutlineThickness = 0.f;
    FloatRect    mInsideBounds;
    FloatRect    mBounds;
};
}