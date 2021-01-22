#pragma once

#include <fluffy/event/event.hpp>
#include <fluffy/graphics/camera.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {

class OrthographicCameraController
{
public:
    explicit OrthographicCameraController(Vector2i viewport, bool rotationEnabled = true, bool zoomEnabled = true);

    OrthographicCamera&       getCamera() { return mCamera; }
    const OrthographicCamera& getCamera() const { return mCamera; }

    void update(Time dt);
    void onEvent(Event& event);

private:
    void onWindowResized(Event& event);

private:
    Vector2i           mViewport;
    bool               mRotationEnabled;
    bool               mZoomEnabled;
    float              mCameraTranslationSpeed = 200.f;
    float              mCameraRotationSpeed    = 20.f;
    float              mCameraZoomFactor       = 1.05f;
    OrthographicCamera mCamera;
};

}
