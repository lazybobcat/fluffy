#include <fluffy/game/camera_controller.hpp>
#include <fluffy/input/input.hpp>

using namespace Fluffy;

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotationEnabled, bool zoomEnabled)
  : mAspectRatio(aspectRatio)
  , mRotationEnabled(rotationEnabled)
  , mZoomEnabled(zoomEnabled)
  , mCamera({ -mAspectRatio, 1.f, 2 * mAspectRatio, 2 * 1.f })
{
}

void OrthographicCameraController::update(Time dt)
{
    if (Input::isKeyPressed(Keyboard::Key::A)) {
        mCamera.move({ -mCameraTranslationSpeed * dt.seconds(), 0.f, 0.f });
    }
    if (Input::isKeyPressed(Keyboard::Key::D)) {
        mCamera.move({ mCameraTranslationSpeed * dt.seconds(), 0.f, 0.f });
    }
    if (Input::isKeyPressed(Keyboard::Key::W)) {
        mCamera.move({ 0.f, mCameraTranslationSpeed * dt.seconds(), 0.f });
    }
    if (Input::isKeyPressed(Keyboard::Key::S)) {
        mCamera.move({ 0.f, -mCameraTranslationSpeed * dt.seconds(), 0.f });
    }

    if (mRotationEnabled) {
        if (Input::isKeyPressed(Keyboard::Key::Q)) {
            mCamera.rotateZ(mCameraRotationSpeed * dt.seconds());
        }
        if (Input::isKeyPressed(Keyboard::Key::E)) {
            mCamera.rotateZ(-mCameraRotationSpeed * dt.seconds());
        }
    }

    if (mZoomEnabled) {
        if (Input::isKeyPressed(Keyboard::Key::NumPadSubtract)) {
            mCamera.zoom(mCameraZoomFactor);
            mCameraTranslationSpeed *= mCameraZoomFactor;
        }
        if (Input::isKeyPressed(Keyboard::Key::NumPadAdd)) {
            float factor = 1.f / mCameraZoomFactor;
            mCamera.zoom(factor);
            mCameraTranslationSpeed *= factor;
        }
    }
}

void OrthographicCameraController::onEvent(Event& event)
{
    if (Event::WindowResized == event.type) {
        onWindowResized(event);
    }
}

void OrthographicCameraController::onWindowResized(Event& event)
{
    mAspectRatio = (float)event.size.size.x / (float)event.size.size.y;
    mCamera.setProjectionMatrix({ -mAspectRatio, 1.f, 2 * mAspectRatio, 2 * 1.f });
}
