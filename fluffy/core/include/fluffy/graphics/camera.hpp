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
    Camera(const Vector2f& center, const Vector2f& size);
    Camera(const Vector3f& position, float fov);

    void setPosition(const Vector2f& position);
    void setPosition(const Vector3f& position);
    void move(const Vector2f& delta);
    void setSize(const Vector2f& size);
    void setViewportSize(const Vector2f& size);
    void setRotation(float degrees);
    void rotate(float degrees);
    void zoom(float factor);
    void setZoom(float zoom);
    // @todo 3D rotations
    void setFOV(float fov);
    void setCameraType(CameraType type);

    [[nodiscard]] Vector3f   getPosition() const;
    [[nodiscard]] Vector2f   getSize() const;
    [[nodiscard]] float      getFOV() const;
    [[nodiscard]] float      getZoom() const;
    [[nodiscard]] CameraType getCameraType() const;
    [[nodiscard]] glm::mat4  getViewProjection() const;

private:
    friend class Painter;

    void updateProjection();

private:
    CameraType mType                = CameraType::Orthographic;
    glm::mat4  mProjection          = glm::mat4(1.f);
    Vector3f   mPosition            = { 0.f, 0.f, 0.f };
    Vector2f   mSize                = { 1280.f, 720.f };
    Vector2f   mViewportSize        = { 1280.f, 720.f };
    float      mZoom                = 1.f;
    float      mRotation            = 0.f;
    float      mFOV                 = 30.f;
    bool       mRecomputeProjection = true;
};
}
