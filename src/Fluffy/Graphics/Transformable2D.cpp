//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 15/04/18.
//

#include <Fluffy/Graphics/Transformable2D.hpp>
#include <cmath>

using namespace Fluffy::Graphics;

void Transformable2D::setOrigin(Fluffy::Graphics::Vector2f origin)
{
    mOrigin = origin;
}

void Transformable2D::setPosition(Vector2f position)
{
    mPosition = position;
}

void Transformable2D::setScale(Vector2f scale)
{
    mScale = scale;
}

void Transformable2D::setRotation(float angle)
{
    mRotation = static_cast<float>(fmod(angle, 360));
    if (mRotation < 0) {
        mRotation += 360.f;
    }
}

Vector2f Transformable2D::getOrigin() const
{
    return mOrigin;
}

Vector2f Transformable2D::getPosition() const
{
    return mPosition;
}

Vector2f Transformable2D::getScale() const
{
    return mScale;
}

float Transformable2D::getRotation() const
{
    return mRotation;
}

void Transformable2D::move(Vector2f offset)
{
    setPosition(mPosition + offset);
}

void Transformable2D::scale(Vector2f factor)
{
    setScale({mScale.x * factor.x, mScale.y * factor.x});
}

void Transformable2D::rotate(float angle)
{
    setRotation(mRotation + angle);
}
