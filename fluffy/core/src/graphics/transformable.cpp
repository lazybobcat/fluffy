#include <fluffy/graphics/transformable.hpp>

using namespace Fluffy;

FloatRect transformRect(const glm::mat4& transform, const FloatRect& bounds)
{
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

/**********************************************************************************************************************/

Transformable::Transformable()
  : mOrigin({ 0.f, 0.f, 0.f })
  , mPosition({ 0.f, 0.f, 0.f })
  , mEulerAngles({ 0.f, 0.f, 0.f })
  , mScale({ 1.f, 1.f, 1.f })
  , mTransform(glm::mat4(1.0f))
  , mInverseTransform(glm::mat4(1.0f))
{
}

void Transformable::setOrigin(const Vector2f& origin)
{
    setOrigin({ origin.x, origin.y, 0.f });
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

void Transformable::setTransformMatrix(const glm::mat4& transform)
{
    mPosition = transform[3];

    for (int i = 0; i < 3; i++) {
        mScale[i] = glm::length(glm::vec3(transform[i]));
    }

    const glm::mat3 rotMtx(
      glm::vec3(transform[0]) / mScale[0],
      glm::vec3(transform[1]) / mScale[1],
      glm::vec3(transform[2]) / mScale[2]);
    auto rotation = glm::conjugate(glm::quat_cast(rotMtx));
    mEulerAngles  = glm::eulerAngles(rotation) * 3.14159f / 180.f;

    FLUFFY_LOG_INFO("angles = {}", mEulerAngles);

    mNeedToUpdate = true;
}

const glm::mat4& Transformable::getTransformMatrix() const
{
    if (mNeedToUpdate) {
        mTransform = glm::translate(glm::mat4(1.f), mPosition) *
                     glm::rotate(glm::mat4(1.f), glm::radians(mEulerAngles.x), { 1, 0, 0 }) *
                     glm::rotate(glm::mat4(1.f), glm::radians(mEulerAngles.y), { 0, -1, 0 }) *
                     glm::rotate(glm::mat4(1.f), glm::radians(mEulerAngles.z), { 0, 0, 1 }) *
                     glm::translate(glm::mat4(1.f), -mOrigin * mScale) *
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