#include <cmath>
#include <fluffy/graphics/painter.hpp>
#include <fluffy/graphics/sprite.hpp>

using namespace Fluffy;

Sprite::Sprite()
  : mVertices(4)
  , mTextureRect()
  , mSize({ 0, 0 })
{
}

Sprite::Sprite(const Ref<Texture2D>& texture)
  : mVertices(4)
  , mTextureRect()
  , mSize({ 0, 0 })
{
    setTexture(texture, true);
}

Sprite::Sprite(const Ref<Texture2D>& texture, const UIntRect& textureRect)
  : mVertices(4)
  , mTextureRect()
  , mSize({ 0, 0 })
{
    setTexture(texture, true);
    setTextureRect(textureRect);
}

void Sprite::setTexture(const Ref<Texture2D>& texture, bool resetRect)
{
    mTexture  = texture;
    auto size = texture->getSize();
    mSize     = size;

    if (resetRect) {
        setTextureRect({ 0, 0, size.x, size.y });
    }
}

void Sprite::setTextureRect(const UIntRect& textureRect)
{
    if (textureRect != mTextureRect) {
        mTextureRect = textureRect;
        updatePositions();
        updateTexCoords();
    }
}

void Sprite::setColor(const Color& color)
{
    mVertices[0].color = color;
    mVertices[1].color = color;
    mVertices[2].color = color;
    mVertices[3].color = color;
}

void Sprite::setSize(const Vector2f& size)
{
    mSize = size;
    updatePositions();
    updateTexCoords();
}

void Sprite::setVisible(bool visible)
{
    mVisible = visible;
}

const Ref<Texture2D>& Sprite::getTexture() const
{
    return mTexture;
}

const UIntRect& Sprite::getTextureRect() const
{
    return mTextureRect;
}

const Color& Sprite::getColor() const
{
    return mVertices[0].color;
}

const VertexVector& Sprite::getVertices() const
{
    return mVertices;
}

const Vector2f& Sprite::getSize() const
{
    return mSize;
}

bool Sprite::isVisible() const
{
    return mVisible;
}

FloatRect Sprite::getLocalBounds() const
{
    auto width  = static_cast<float>(std::fabs(mSize.x));
    auto height = static_cast<float>(std::fabs(mSize.y));

    return { 0.f, 0.f, width, height };
}

FloatRect Sprite::getGlobalBounds(const glm::mat4& transform) const
{
    auto bounds = getLocalBounds();

    return transformRect(transform, bounds);
}

void Sprite::draw(Painter& painter, RenderStates states) const
{
    if (mTexture && mVisible) {
        states.texture = mTexture;
        // Todo: material (shader, ...)
        painter.drawQuad(mVertices, states);
    }
}

void Sprite::updatePositions()
{
    auto bounds = getLocalBounds();

    mVertices[0].position = { 0.f, 0.f, 0.f };
    mVertices[1].position = { bounds.width, 0.f, 0.f };
    mVertices[2].position = { bounds.width, bounds.height, 0.f };
    mVertices[3].position = { 0.f, bounds.height, 0.f };
}

void Sprite::updateTexCoords()
{
    if (mTexture) {
        auto texSize = mTexture->getSize();
        auto left    = static_cast<float>(mTextureRect.left) / static_cast<float>(texSize.x);
        auto width   = (left + mTextureRect.width);
        auto right   = (width / static_cast<float>(texSize.x));
        auto top     = static_cast<float>(mTextureRect.top) / static_cast<float>(texSize.y);
        auto height  = (top + mTextureRect.height);
        auto bottom  = (height / static_cast<float>(texSize.y));

        if (mTexture->isRepeated()) {
            right *= (mSize.x / texSize.x);
            bottom *= (mSize.y / texSize.y);
        }

        mVertices[0].texCoords = Vector2f(left, top);
        mVertices[1].texCoords = Vector2f(right, top);
        mVertices[2].texCoords = Vector2f(right, bottom);
        mVertices[3].texCoords = Vector2f(left, bottom);
    }
}
