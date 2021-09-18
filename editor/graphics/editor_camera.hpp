#pragma once

#include <fluffy/event/event.hpp>
#include <fluffy/graphics/camera.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {

class EditorCamera : public PerspectiveCamera
{
public:
    EditorCamera();
    EditorCamera(float fov, float aspectRatio, float near, float far);

    void resetRotation();

    void onUpdate(Time dt);
    void onEvent(Event& event);

private:
    void onMousePan(const Vector2f& delta);
    void onMouseRotate(const Vector2f& delta);
    void onMouseZoom(float delta);

    Vector2f getPanSpeed() const;
    float    getRotationSpeed() const;
    float    getZoomSpeed() const;

private:
    Vector2f mInitialMousePosition = { 0.f, 0.f };
};
}