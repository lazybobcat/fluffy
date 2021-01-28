#pragma once

#include <entt/entt.hpp>
#include <fluffy/assert.hpp>
#include <fluffy/definitions.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/scene/entity_registry.hpp>

namespace Fluffy {

class Entity
{
public:
    static Entity INVALID;

public:
    Entity() = default;
    Entity(entt::entity handle, EntityRegistry* registry);
    Entity(const Entity&) = default;
    Entity(Entity&&)      = default;
    Entity& operator=(const Entity&) = default;

    operator bool() const;
    operator entt::entity() const;
    operator std::uint32_t() const;
    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;

    template<typename T>
    bool has()
    {
        FLUFFY_ASSERT(mRegistry, "The entity does not belong to any registry, you should not be using this entity");

        return mRegistry->has<T>(mEntity);
    }

    template<typename T, typename... Args>
    T& add(Args... args)
    {
        FLUFFY_ASSERT(mRegistry, "The entity does not belong to any registry, you should not be using this entity");

        return mRegistry->emplace<T>(mEntity, std::forward<Args>(args)...);
    }

    template<typename T>
    T& get()
    {
        FLUFFY_ASSERT(mRegistry, "The entity does not belong to any registry, you should not be using this entity");

        return mRegistry->get<T>(mEntity);
    }

    template<typename T>
    void remove()
    {
        FLUFFY_ASSERT(mRegistry, "The entity does not belong to any registry, you should not be using this entity");

        return mRegistry->remove<T>(mEntity);
    }

private:
    entt::entity    mEntity = entt::null;
    EntityRegistry* mRegistry = nullptr;
};
}