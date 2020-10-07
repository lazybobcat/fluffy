#include <fluffy/graphics/transformable.hpp>

using namespace Fluffy;

Transformable::Transformable()
  : mOrigin({ 0.f, 0.f, 0.f })
  , mPosition({ 0.f, 0.f, 0.f })
  , mEulerAngles({ 0.f, 0.f, 0.f })
  , mScale({ 1.f, 1.f, 1.f })
{
}

void Transformable::setOrigin(const Vector3f& origin)
{
    mOrigin       = origin;
    mNeedToUpdate = true;
}

Vector3f Transformable::getOrigin() const
{
    return mOrigin;
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
const Transform& Transformable::getTransform() const
{
    if (mNeedToUpdate) {
        mTransform = Transform::Identity;

        // @todo : maybe use quaternion instead
        mTransform.rotate(mEulerAngles.y, mOrigin, { 0, 1, 0 });
        mTransform.rotate(mEulerAngles.z, mOrigin, { 0, 0, 1 });
        mTransform.rotate(mEulerAngles.x, mOrigin, { 1, 0, 0 });
        mTransform.translate(mPosition - mOrigin);
        mTransform.scale(mScale, mOrigin);

        mNeedToUpdate        = false;
        mNeedToUpdateInverse = true;
    }

    return mTransform;
}

const Transform& Transformable::getInverseTransform() const
{
    if (mNeedToUpdate || mNeedToUpdateInverse) {
        mInverseTransform    = glm::inverse(getTransform().getMatrix());
        mNeedToUpdateInverse = false;
    }

    return mInverseTransform;
}
