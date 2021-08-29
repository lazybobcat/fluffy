#pragma once

#include <fluffy/math/math.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class Transformable
{
public:
    Transformable();
    virtual ~Transformable() = default;

    void     setOrigin(const Vector2f& origin);
    void     setOrigin(const Vector3f& origin);
    Vector3f getOrigin() const;

    void     setPosition(const Vector2f& position);
    void     setPosition(const Vector3f& position);
    void     move(const Vector2f& delta);
    void     move(const Vector3f& delta);
    Vector3f getPosition() const;

    void     setScale(const Vector2f& scale);
    void     setScale(const Vector3f& scale);
    Vector3f getScale() const;

    void     setRotation(const Vector2f& eulerAngles);
    void     setRotation(const Vector3f& eulerAngles);
    void     rotateX(float degrees);
    void     rotateY(float degrees);
    void     rotateZ(float degrees);
    Vector3f getEulerAngles() const;

    const glm::mat4& getTransformMatrix() const;
    const glm::mat4& getInverseTransform() const;

private:
    Vector3f          mOrigin;
    Vector3f          mPosition;
    Vector3f          mEulerAngles;
    Vector3f          mScale;
    mutable glm::mat4 mTransform;
    mutable glm::mat4 mInverseTransform;
    mutable bool      mNeedToUpdate        = true;
    mutable bool      mNeedToUpdateInverse = true;
};
}
