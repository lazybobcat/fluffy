#pragma once

#include <entt/entt.hpp>
#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/rectangle_shape.hpp>
#include <fluffy/graphics/sprite.hpp>
#include <fluffy/graphics/transformable.hpp>

namespace Fluffy {

struct TagComponent
{
    TagComponent() = default;
    explicit TagComponent(const String& tag)
      : tag(tag)
    {}

    String tag;

#if FLUFFY_DEBUG
    const String toString() const
    {
        return fmt::format("'TagComponent' {{tag:{}}}", tag);
    }
#endif
};

struct TransformComponent : public Transformable
{
    TransformComponent() = default;

#if FLUFFY_DEBUG
    const String toString() const
    {
        return "'TransformComponent' {}";
    }
#endif
};

struct SpriteComponent
{
    SpriteComponent()
      : sprite()
    {}

    Sprite sprite;

#if FLUFFY_DEBUG
    const String toString() const
    {
        return "'SpriteComponent' {}";
    }
#endif
};

struct CameraComponent
{
    CameraComponent()
    {
        recreateCamera();
    }

    ~CameraComponent()
    {
        delete camera;
    }

    void changeCamera(Camera::CameraType t)
    {
        type = t;
        recreateCamera();
    }

    void recreateCamera()
    {
        delete camera;
        if (Camera::CameraType::Perspective == type) {
            camera = new PerspectiveCamera(45.f, 1920.f / 1080.f, 0.1f, 1000000.f);
        } else {
            camera = new OrthographicCamera({ 0, 0 }, { 1920.f, 1080.f });
        }
    }

    Camera*            camera           = nullptr;
    Camera::CameraType type             = Camera::CameraType::Perspective;
    bool               fixedAspectRatio = false;

#if FLUFFY_DEBUG
    const String toString() const
    {
        return fmt::format("'CameraComponent' {{type: {}, fixedAspectRatio:{}}}", type, fixedAspectRatio);
    }
#endif
};

}