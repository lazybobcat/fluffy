#include "editor_camera.hpp"
#include <fluffy/input/input.hpp>

using namespace Fluffy;

EditorCamera::EditorCamera()
  : PerspectiveCamera()
{
}

EditorCamera::EditorCamera(float fov, float aspectRatio, float near, float far)
  : PerspectiveCamera(fov, aspectRatio, near, far)
{
}

void EditorCamera::resetRotation()
{
    mPitch = 0.f;
    mYaw   = 0.f;
    updateView();
}

void EditorCamera::onUpdate(Time dt)
{
    Vector2f  mouse       = Input::getMousePosition();
    glm::vec2 delta       = (mouse - mInitialMousePosition) * 0.003f;
    mInitialMousePosition = mouse;

    if (Input::isKeyPressed(Keyboard::Key::LeftAlt)) {
        if (Input::isMouseButtonPressed(Mouse::Button::ButtonLeft)) {
            onMouseRotate(delta);
        }
    } else if (Input::isKeyPressed(Keyboard::Key::Space)) {
        if (Input::isMouseButtonPressed(Mouse::Button::ButtonLeft)) {
            onMousePan(delta);
        }
    }

    updateView();
}

void EditorCamera::onEvent(Event& event)
{
    if (Event::MouseWheelScrolled == event.type) {
        onMouseZoom(event.mouseWheel.delta.y);
        updateView();
        event.stopPropagation();
    }
}

void EditorCamera::onMousePan(const Vector2f& delta)
{
    auto speed = getPanSpeed();
    mFocalPoint += -getRightDirection() * delta.x * speed.x * mDistance;
    mFocalPoint += -getUpwardDirection() * delta.y * speed.y * mDistance;
}

void EditorCamera::onMouseRotate(const Vector2f& delta)
{
    float yawSign = getUpwardDirection().y < 0 ? 1.0f : -1.0f;
    mYaw += yawSign * delta.x * getRotationSpeed();
    mPitch += delta.y * getRotationSpeed();
}

void EditorCamera::onMouseZoom(float delta)
{
    mDistance -= delta * getZoomSpeed();
    if (mDistance < 1.0f) {
        mFocalPoint -= getForwardDirection();
        mDistance = 100.0f;
    }
}

Vector2f EditorCamera::getPanSpeed() const
{
    float x       = std::min(mViewport.width / 1000.0f, 2.4f); // max = 2.4f
    float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

    float y       = std::min(mViewport.height / 1000.0f, 2.4f); // max = 2.4f
    float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

    return { xFactor, yFactor };
}

float EditorCamera::getRotationSpeed() const
{
    return 0.8f;
}

float EditorCamera::getZoomSpeed() const
{
    float distance = mDistance * 0.2f;
    distance       = std::max(distance, 0.0f);
    float speed    = distance * distance;
    speed          = std::min(speed, 100.0f); // max speed = 100
    return speed;
}
