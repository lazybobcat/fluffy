#include <fluffy/graphics/transformable.hpp>

using namespace Fluffy;

Transformable::Transformable()
  : mPosition({ 0.f, 0.f, 0.f })
  , mEulerAngles({ 0.f, 0.f, 0.f })
  , mScale({ 1.f, 1.f, 1.f })
  , mTransform(glm::mat4(1.0f))
  , mInverseTransform(glm::mat4(1.0f))
{
}

void Transformable::setPosition(const Vector2f& position)
{
    setPosition({ position.x, position.y, 0.f });
}

void Transformable::setPosition(const Vector3f& position)
{
    mPosition     = position;
    mNeedToUpdate = true;
}

void Transformable::move(const Vector2f& delta)
{
    move({ delta.x, delta.y, 0 });
}

void Transformable::move(const Vector3f& delta)
{
    mPosition += delta;
    mNeedToUpdate = true;
}

Vector3f Transformable::getPosition() const
{
    return mPosition;
}

void Transformable::setScale(const Vector2f& scale)
{
    setScale({ scale.x, scale.y, 1.f });
}

void Transformable::setScale(const Vector3f& scale)
{
    mScale        = scale;
    mNeedToUpdate = true;
}

Vector3f Transformable::getScale() const
{
    return mScale;
}

void Transformable::setRotation(const Vector2f& eulerAngles)
{
    mEulerAngles.x = eulerAngles.x;
    mEulerAngles.y = eulerAngles.y;
    mNeedToUpdate  = true;
}

void Transformable::setRotation(const Vector3f& eulerAngles)
{
    mEulerAngles.x = eulerAngles.x;
    mEulerAngles.y = eulerAngles.y;
    mEulerAngles.z = eulerAngles.z;
    mNeedToUpdate  = true;
}

void Transformable::rotateX(float degrees)
{
    mEulerAngles.x += degrees;
    mNeedToUpdate = true;
}

void Transformable::rotateY(float degrees)
{
    mEulerAngles.y += degrees;
    mNeedToUpdate = true;
}

void Transformable::rotateZ(float degrees)
{
    mEulerAngles.z += degrees;
    mNeedToUpdate = true;
}

Vector3f Transformable::getEulerAngles() const
{
    return mEulerAngles;
}
const glm::mat4& Transformable::getTransformMatrix() const
{
    if (mNeedToUpdate) {
        mTransform = glm::translate(glm::mat4(1.f), mPosition) *
                     glm::rotate(glm::mat4(1.f), glm::radians(mEulerAngles.x), { 1, 0, 0 }) *
                     glm::rotate(glm::mat4(1.f), glm::radians(mEulerAngles.y), { 0, 1, 0 }) *
                     glm::rotate(glm::mat4(1.f), glm::radians(mEulerAngles.z), { 0, 0, 1 }) *
                     glm::scale(glm::mat4(1.f), mScale);

        mNeedToUpdate        = false;
        mNeedToUpdateInverse = true;
    }

    return mTransform;
}

const glm::mat4& Transformable::getInverseTransform() const
{
    if (mNeedToUpdate || mNeedToUpdateInverse) {
        mInverseTransform    = glm::inverse(getTransformMatrix());
        mNeedToUpdateInverse = false;
    }

    return mInverseTransform;
}
