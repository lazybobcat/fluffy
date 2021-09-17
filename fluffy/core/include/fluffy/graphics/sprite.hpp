#pragma once

#include <fluffy/graphics/drawable.hpp>
#include <fluffy/graphics/transformable.hpp>
#include <fluffy/graphics/vertex.hpp>

namespace Fluffy {

class Painter;

class Sprite : public Drawable
{
public:
    Sprite();
    explicit Sprite(const Ref<Texture2D>& texture);
    Sprite(const Ref<Texture2D>& texture, const UIntRect& textureRect);

    // @TODO materials

    void setTexture(const Ref<Texture2D>& texture, bool resetRect = true);
    void setTextureRect(const UIntRect& textureRect);
    void setColor(const Color& color);
    void setSize(const Vector2f& size);
    void setVisible(bool visible);

    const Ref<Texture2D>& getTexture() const;
    const UIntRect&       getTextureRect() const;
    const Color&          getColor() const;
    const Vector2f&       getSize() const;
    bool                  isVisible() const;

    /**
     * Get the local bounding rect (transformations not taken into account)
     */
    FloatRect getLocalBounds() const;

    /**
     * Get the bounding rect in global (world) coordinates
     */
    FloatRect getGlobalBounds(const glm::mat4& transform) const;

    const VertexVector& getVertices() const;

private:
    friend class Painter;

    void draw(Painter& painter, RenderStates states) const override;
    void updatePositions();
    void updateTexCoords();

private:
    VertexVector   mVertices;
    Ref<Texture2D> mTexture;
    UIntRect       mTextureRect;
    Vector2f       mSize;
    bool           mVisible = true;
};
}
