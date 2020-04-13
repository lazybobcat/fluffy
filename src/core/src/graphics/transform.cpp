#include <fluffy/graphics/transform.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace Fluffy;

const Transform Transform::Identity;

Transform::Transform()
  : mMatrix(1.f)
{
}

Transform::Transform(float aa, float ab, float ac, float ad, float ba, float bb, float bc, float bd, float ca, float cb, float cc, float cd, float da, float db, float dc, float dd)
  : mMatrix(aa, ab, ac, ad, ba, bb, bc, bd, ca, cb, cc, cd, da, db, dc, dd)
{
}

const float* Transform::getData() const
{
    return glm::value_ptr(mMatrix);
}

Vector3f Transform::transformPoint(const Vector3f& point)
{
    return mMatrix * glm::vec4(point.x, point.y, point.z, 1.f);
}

Transform& Transform::combine(const Transform& transform)
{
    return combine(transform.mMatrix);
}

Transform& Transform::combine(const glm::mat4& matrix)
{
    mMatrix = mMatrix * matrix;

    return *this;
}

Transform& Transform::translate(const Vector3f& vector)
{
    mMatrix = glm::translate(mMatrix, vector);

    return *this;
}

Transform& Transform::rotate(float degrees, const Vector3f& center, const Vector3f& axis)
{
    translate(center);
    mMatrix = glm::rotate(mMatrix, glm::radians(degrees), axis);
    translate(-center);

    return *this;
}

Transform& Transform::scale(const Vector3f& scale, const Vector3f& center)
{
    translate(center);
    mMatrix = glm::scale(mMatrix, scale);
    translate(-center);

    return *this;
}

bool Transform::operator==(const Transform& rhs) const
{
    return mMatrix[0] == rhs.mMatrix[0] && mMatrix[1] == rhs.mMatrix[1] && mMatrix[2] == rhs.mMatrix[2] &&
           mMatrix[3] == rhs.mMatrix[3] && mMatrix[4] == rhs.mMatrix[4] && mMatrix[5] == rhs.mMatrix[5] &&
           mMatrix[6] == rhs.mMatrix[6] && mMatrix[7] == rhs.mMatrix[7] && mMatrix[8] == rhs.mMatrix[8];
}

bool Transform::operator!=(const Transform& rhs) const
{
    return !(rhs == *this);
}
