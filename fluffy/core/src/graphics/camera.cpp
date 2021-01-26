#include <fluffy/graphics/camera.hpp>

using namespace Fluffy;

/**
 * Note: The Y-axis is pointing down so that (0,0) is on the top-left.
 * For that, we invert to top and bottom coordinates of the projection matrix.
 */

Camera::Camera(const Vector2f& center, const Vector2f& size)
  : mPosition(center, 0.f)
  , mSize(size)
{
}

Camera::Camera(const Vector3f& position, float fov)
  : mPosition(position)
  , mFOV(fov)
  , mType(CameraType::Perspective)
{
}

void Camera::updateProjection()
{
    if (mRecomputeProjection) {
        // Orthographic camera
        if (mType == CameraType::Orthographic) {
            float AR         = mSize.x / mSize.y;
            float viewportAR = mViewportSize.x / mViewportSize.y;

            if (viewportAR >= AR) {
                float coeff = viewportAR / AR;
                mProjection = glm::ortho(-mSize.x / 2.f * coeff, mSize.x / 2.f * coeff, mSize.y / 2.f, -mSize.y / 2.f, -1000.f, 1000.f);
            } else {
                float coeff = AR / viewportAR;
                mProjection = glm::ortho(-mSize.x / 2.f, mSize.x / 2.f, mSize.y / 2.f * coeff, -mSize.y / 2.f * coeff, -1000.f, 1000.f);
            }

            if (mZoom != 1.f) {
                mProjection = glm::scale(mProjection, { mZoom, mZoom, mZoom });
            }
            if (mRotation != 0.f) {
                mProjection = glm::rotate(mProjection, glm::radians(mRotation), { 0.f, 0.f, 1.f });
            }
            mProjection = glm::translate(mProjection, -mPosition);
        } else {
            // @todo
        }

        mRecomputeProjection = false;
    }
}

glm::mat4 Camera::getViewProjection() const
{
    return mProjection;
}

void Camera::move(const Vector2f& delta)
{
    mPosition.x += delta.x;
    mPosition.y += delta.y;
    mRecomputeProjection = true;
}

void Camera::setPosition(const Vector2f& position)
{
    setPosition({ position.x, position.y, 0.f });
}

void Camera::setPosition(const Vector3f& position)
{
    mPosition            = position;
    mRecomputeProjection = true;
}

void Camera::setSize(const Vector2f& size)
{
    mSize                = size;
    mRecomputeProjection = true;
}

void Camera::setViewportSize(const Vector2f& size)
{
    mViewportSize        = size;
    mRecomputeProjection = true;
}

void Camera::setRotation(float degrees)
{
    mRotation            = degrees;
    mRecomputeProjection = true;
}

void Camera::rotate(float degrees)
{
    mRotation += degrees;
    mRecomputeProjection = true;
}

void Camera::setFOV(float fov)
{
    mFOV                 = fov;
    mRecomputeProjection = true;
}

void Camera::zoom(float factor)
{
    mZoom *= factor;
    mRecomputeProjection = true;
}

void Camera::setZoom(float zoom)
{
    mZoom = zoom;
    mRecomputeProjection = true;
}

void Camera::setCameraType(Camera::CameraType type)
{
    mType                = type;

}

Vector3f Camera::getPosition() const
{
    return mPosition;
}

Vector2f Camera::getSize() const
{
    return mSize;
}

float Camera::getFOV() const
{
    return mFOV;
}

Camera::CameraType Camera::getCameraType() const
{
    return mType;
}

float Camera::getZoom() const
{
    return mZoom;
}
