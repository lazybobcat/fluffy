#pragma once

#include <fluffy/event/event.hpp>
#include <fluffy/graphics/camera.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {

class OrthographicCameraController
{
public:
    explicit OrthographicCameraController(float aspectRatio, bool rotationEnabled = true, bool zoomEnabled = true);

    OrthographicCamera&       getCamera() { return mCamera; }
    const OrthographicCamera& getCamera() const { return mCamera; }

    void update(Time dt);
    void onEvent(Event& event);

private:
    void onWindowResized(Event& event);

private:
    float              mAspectRatio;
    bool               mRotationEnabled;
    bool               mZoomEnabled;
    float              mCameraTranslationSpeed = 1.f;
    float              mCameraRotationSpeed    = 20.f;
    float              mCameraZoomFactor       = 1.05f;
    OrthographicCamera mCamera;
};

}
