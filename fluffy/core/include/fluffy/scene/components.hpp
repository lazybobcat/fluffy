#pragma once

#include <entt/entt.hpp>
#include <fluffy/graphics/rectangle_shape.hpp>
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
      : rectangle({ 10.f, 10.f })
    {}

    RectangleShape rectangle;

#if FLUFFY_DEBUG
    const String toString() const
    {
        return "'SpriteComponent' {}";
    }
#endif
};

}