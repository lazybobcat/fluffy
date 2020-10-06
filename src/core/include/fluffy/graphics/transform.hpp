#pragma once

#include <fluffy/math/math.hpp>

namespace Fluffy {

#define TRANSFORM_NB_COMPONENTS 16

class Transform
{
public:
    Transform();

    const float* getData() const;

    Vector3f transformPoint(const Vector3f& point);

    Transform& combine(const Transform& transform);
    Transform& translate(const Vector3f& vector);
    Transform& rotate(float degrees, const Vector3f& center, const Vector3f& axis = { 0, 0, 1 });
    Transform& scale(const Vector3f& scale, const Vector3f& center);

    bool operator==(const Transform& rhs) const;
    bool operator!=(const Transform& rhs) const;

    static const Transform Identity;

private:
    Transform(float aa, float ab, float ac, float ad, float ba, float bb, float bc, float bd, float ca, float cb, float cc, float cd, float da, float db, float dc, float dd);
    Transform& combine(const glm::mat4& matrix);

private:
    glm::mat4 mMatrix;
};
}
