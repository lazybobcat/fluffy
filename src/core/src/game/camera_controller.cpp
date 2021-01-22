#include <fluffy/game/camera_controller.hpp>
#include <fluffy/input/input.hpp>

using namespace Fluffy;

OrthographicCameraController::OrthographicCameraController(Vector2i viewport, bool rotationEnabled, bool zoomEnabled)
  : mViewport(viewport)
  , mRotationEnabled(rotationEnabled)
  , mZoomEnabled(zoomEnabled)
  , mCamera({ { -viewport.x / 2.f, viewport.y / 2.f }, { (float)viewport.x, (float)viewport.y } })
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
        mCamera.move({ 0.f, -mCameraTranslationSpeed * dt.seconds(), 0.f });
    }
    if (Input::isKeyPressed(Keyboard::Key::S)) {
        mCamera.move({ 0.f, mCameraTranslationSpeed * dt.seconds(), 0.f });
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
    mViewport = event.size.size;
    mCamera.setProjectionMatrix({ { -mViewport.x / 2.f, mViewport.y / 2.f }, { (float)mViewport.x, (float)mViewport.y } });
}
