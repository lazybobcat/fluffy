#include <fluffy/assert.hpp>
#include <fluffy/graphics/camera.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace Fluffy;

Camera::Camera(const glm::mat4& projection)
  : mProjection(projection)
{
}

const glm::mat4& Camera::getProjectionMatrix() const
{
    return mProjection;
}

const glm::mat4& Camera::getViewMatrix() const
{
    return mView;
}

void Camera::setViewport(const FloatRect& viewport)
{
    FLUFFY_ASSERT(viewport.left >= 0 && viewport.left <= 1, "Camera viewport left coordinate must be between 0 and 1");
    FLUFFY_ASSERT(viewport.top >= 0 && viewport.top <= 1, "Camera viewport top coordinate must be between 0 and 1");
    FLUFFY_ASSERT(viewport.width >= 0 && viewport.width <= 1, "Camera viewport width must be between 0 and 1");
    FLUFFY_ASSERT(viewport.height >= 0 && viewport.height <= 1, "Camera viewport height must be between 0 and 1");

    mViewport = viewport;
}

FloatRect Camera::getViewport() const
{
    return mViewport;
}

void Camera::setTargetSize(const Vector2f& size)
{
    mTargetSize = size;
}

Vector2f Camera::getTargetSize() const
{
    return mTargetSize;
}

/**********************************************************************************************************************/

/**
 * Note: The Y-axis is pointing down so that (0,0) is on the top-left.
 * For that, we invert to top and bottom coordinates of the projection matrix.
 */

OrthographicCamera::OrthographicCamera(const Vector2f& center, const Vector2f& size)
  : mPosition(center, 0.f)
  , mSize(size)
{
}

void OrthographicCamera::updateProjection()
{
    if (mRecomputeProjection) {
        // TRANSFORM
        mTransform = glm::translate(glm::mat4(1.f), mPosition) *
                     glm::rotate(glm::mat4(1.f), glm::radians(mRotation), { 0, 0, 1 }) *
                     glm::scale(glm::mat4(1.f), { 1.f, 1.f, 1 / mZoom });

        // VIEW PROJECTION
        float AR         = mSize.x / mSize.y;
        float viewportAR = mTargetSize.x / mTargetSize.y;

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
        mProjection     = glm::translate(mProjection, -mPosition);
        mViewProjection = mProjection * glm::inverse(mTransform);

        mRecomputeProjection = false;
    }
}

void OrthographicCamera::move(const Vector2f& delta)
{
    mPosition.x += delta.x;
    mPosition.y += delta.y;
    mRecomputeProjection = true;
}

void OrthographicCamera::setPosition(const Vector2f& position)
{
    setPosition({ position.x, position.y, 0.f });
}

void OrthographicCamera::setPosition(const Vector3f& position)
{
    mPosition            = position;
    mRecomputeProjection = true;
}

void OrthographicCamera::setSize(const Vector2f& size)
{
    mSize                = size;
    mRecomputeProjection = true;
}

void OrthographicCamera::setViewport(const FloatRect& viewport)
{
    Camera::setViewport(viewport);
    mRecomputeProjection = true;
}

void OrthographicCamera::setTargetSize(const Vector2f& size)
{
    Camera::setTargetSize(size);
    mRecomputeProjection = true;
}

void OrthographicCamera::setRotation(float degrees)
{
    mRotation            = degrees;
    mRecomputeProjection = true;
}

void OrthographicCamera::rotate(float degrees)
{
    mRotation += degrees;
    mRecomputeProjection = true;
}

void OrthographicCamera::zoom(float factor)
{
    mZoom *= factor;
    mRecomputeProjection = true;
}

void OrthographicCamera::setZoom(float zoom)
{
    mZoom                = zoom;
    mRecomputeProjection = true;
}

Vector3f OrthographicCamera::getPosition() const
{
    return mPosition;
}

Vector2f OrthographicCamera::getSize() const
{
    return mSize;
}

float OrthographicCamera::getZoom() const
{
    return mZoom;
}

const glm::mat4& OrthographicCamera::getViewProjectionMatrix() const
{
    return mViewProjection;
}

Camera::CameraType OrthographicCamera::getType() const
{
    return CameraType::Orthographic;
}

/**********************************************************************************************************************/

PerspectiveCamera::PerspectiveCamera()
  : Camera(glm::perspective(glm::radians(45.f), 16.f / 9.f, 0.1f, 1000000.f))
{
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far)
  : mFov(fov)
  , mAspectRatio(aspectRatio)
  , mNear(near)
  , mFar(far)
  , Camera(glm::perspective(glm::radians(fov), aspectRatio, near, far))
{
    updateView();
}

void PerspectiveCamera::setTargetSize(const Vector2f& size)
{
    Camera::setTargetSize(size);
    mAspectRatio = size.x / size.y;
    updateProjection();
}

void PerspectiveCamera::updateProjection()
{
    mProjection = glm::perspective(glm::radians(mFov), mAspectRatio, mNear, mFar);

    mViewProjection = mProjection * mView;
}

void PerspectiveCamera::updateView()
{
    mPosition             = calculatePosition();
    glm::quat orientation = getOrientation();

    mView = glm::translate(glm::mat4(1.f), mPosition) * glm::toMat4(orientation);
    mView = glm::inverse(mView);

    mViewProjection = mProjection * mView;
}

const glm::mat4& PerspectiveCamera::getViewProjectionMatrix() const
{
    return mViewProjection;
}

Camera::CameraType PerspectiveCamera::getType() const
{
    return Camera::CameraType::Perspective;
}

glm::quat PerspectiveCamera::getOrientation() const
{
    return { glm::vec3(-mPitch + glm::radians(180.f), -mYaw, 0.0f) };
}

Vector3f PerspectiveCamera::calculatePosition() const
{
    return mFocalPoint - getForwardDirection() * mDistance;
}

Vector3f PerspectiveCamera::getForwardDirection() const
{
    return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}

Vector3f PerspectiveCamera::getUpwardDirection() const
{
    return glm::rotate(getOrientation(), glm::vec3(0.0f, -1.0f, 0.0f));
}

Vector3f PerspectiveCamera::getRightDirection() const
{
    return glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

void PerspectiveCamera::setDistance(float distance)
{
    mDistance = distance;
    updateView();
}

void PerspectiveCamera::setLookAt(const Vector3f& point)
{
    mFocalPoint = point;
    updateView();
}
