#pragma once

#include <fluffy/graphics/transformable.hpp>
#include <fluffy/math/rectangle.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class Painter;

namespace EnumNames {
const std::array<const char*, 2> CameraType({ { "Orthographic", "Perspective" } });
}

class Camera
{
public:
    enum class CameraType
    {
        Orthographic,
        Perspective
    };

public:
    Camera() = default;
    explicit Camera(const glm::mat4& projection);
    virtual ~Camera() = default;

    virtual void            setViewport(const FloatRect& viewport); // Relative coordinates [0, 1]
    [[nodiscard]] FloatRect getViewport() const;

    virtual void           setTargetSize(const Vector2f& size);
    [[nodiscard]] Vector2f getTargetSize() const;

    virtual const glm::mat4& getProjectionMatrix() const;
    virtual const glm::mat4& getViewMatrix() const;
    virtual const glm::mat4& getViewProjectionMatrix() const = 0;
    virtual CameraType       getType() const                 = 0;

protected:
    friend Painter;

    virtual void updateProjection() = 0;

protected:
    glm::mat4 mProjection = glm::mat4(1.f);
    glm::mat4 mView       = glm::mat4(1.f);
    FloatRect mViewport   = { 0.f, 0.f, 1.f, 1.f };
    Vector2f  mTargetSize = { 1280.f, 720.f };
};

class OrthographicCamera : public Camera
{

public:
    OrthographicCamera() = default;
    OrthographicCamera(const Vector2f& center, const Vector2f& size);

    void setPosition(const Vector2f& position);
    void setPosition(const Vector3f& position);
    void move(const Vector2f& delta);
    void setSize(const Vector2f& size);
    void setRotation(float degrees);
    void rotate(float degrees);
    void zoom(float factor);
    void setZoom(float zoom);

    virtual void setViewport(const FloatRect& viewport);
    virtual void setTargetSize(const Vector2f& size);

    const glm::mat4& getViewProjectionMatrix() const override;
    CameraType       getType() const override;

    Vector3f getPosition() const;
    Vector2f getSize() const;
    float    getRotation() const;
    float    getZoom() const;

protected:
    friend class Painter;

    void updateProjection() override;

private:
    glm::mat4 mTransform           = glm::mat4(1.f);
    glm::mat4 mViewProjection      = glm::mat4(1.f);
    Vector3f  mPosition            = { 0.f, 0.f, 0.f };
    Vector2f  mSize                = { 1280.f, 720.f };
    float     mZoom                = 1.f;
    float     mRotation            = 0.f;
    bool      mRecomputeProjection = true;
};

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera();
    PerspectiveCamera(float fov, float aspectRatio, float near, float far);

    void setTargetSize(const Vector2f& size) override;

    const glm::mat4& getViewProjectionMatrix() const override;
    CameraType       getType() const override;

    glm::quat getOrientation() const;
    Vector3f  getForwardDirection() const;
    Vector3f  getUpwardDirection() const;
    Vector3f  getRightDirection() const;

    void  setDistance(float distance);
    float getDistance() const { return mDistance; }

    void            setLookAt(const Vector3f& point);
    const Vector3f& getLookAt() const { return mFocalPoint; }

    void  setPitch(float pitch);
    float getPitch() const { return mPitch; }

    void  setYaw(float yaw);
    float getYaw() const { return mYaw; }

    void  setFov(float fov);
    float getFov() const { return mFov; }

    void  setAspectRatio(float ar);
    float getAspectRatio() const { return mAspectRatio; }

    void  setNear(float near);
    float getNear() const { return mNear; }

    void  setFar(float far);
    float getFar() const { return mFar; }

    const Vector3f& getPosition() const { return mPosition; }

protected:
    void updateProjection() override;
    void updateView();

    Vector3f calculatePosition() const;

protected:
    float mFov         = 45.f;
    float mAspectRatio = 16.f / 9.f;
    float mNear        = 0.1f;
    float mFar         = 1000000.f;
    float mDistance    = 1000.f;
    float mPitch       = 0.f;
    float mYaw         = 0.f;

    Vector3f  mPosition             = { 0.f, 0.f, 0.f };
    Vector3f  mFocalPoint           = { 0.f, 0.f, 0.f };
    Vector2f  mInitialMousePosition = { 0.f, 0.f };
    Vector2f  mSize                 = { 1280.f, 720.f };
    glm::mat4 mViewProjection       = glm::mat4(1.f);
};
}
