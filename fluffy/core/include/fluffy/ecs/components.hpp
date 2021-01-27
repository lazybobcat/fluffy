#pragma once

#include <fluffy/ecs/component.hpp>
#include <fluffy/graphics/rectangle_shape.hpp>
#include <fluffy/graphics/transformable.hpp>

namespace Fluffy {

struct TagComponent : public Component<TagComponent>
{
    TagComponent() = default;
    explicit TagComponent(const String& tag)
      : tag(tag)
    {}

    String tag;

#if FLUFFY_DEBUG
    const String toString() const override
    {
        return fmt::format("'TagComponent' {{tag:{}}}", tag);
    }
#endif
};

struct TransformComponent : public Component<TransformComponent>
  , public Transformable
{
    TransformComponent() = default;

#if FLUFFY_DEBUG
    const String toString() const override
    {
        return "'TransformComponent' {}";
    }
#endif
};

struct SpriteComponent : public Component<SpriteComponent>
{
    SpriteComponent()
      : rectangle({ 10.f, 10.f })
    {}

    RectangleShape rectangle;

#if FLUFFY_DEBUG
    const String toString() const override
    {
        return "'SpriteComponent' {}";
    }
#endif
};

}