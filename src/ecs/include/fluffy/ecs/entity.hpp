#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/event/event.hpp>
#include <fluffy/pch.hpp>

#if FLUFFY_DEBUG
#include <fluffy/pch.hpp>
#endif

namespace Fluffy {

constexpr std::size_t MAX_COMPONENTS = FLUFFY_ECS_MAX_COMPONENTS;

class EntityManager;
template<typename C>
class ComponentHandle;

class Entity
{
public:
    struct Id
    {
        Id() = default;
        Id(const Id& other);
        Id(std::uint64_t id);
        Id(std::uint32_t index, std::uint32_t version);

        std::uint64_t id() const;
        std::uint32_t index() const;
        std::uint32_t version() const;

        bool operator==(const Id& other) const;
        bool operator!=(const Id& other) const;
        bool operator<(const Id& other) const;

    private:
        friend class EntityManager;

    private:
        std::uint64_t mId = 0;
    };

    static const Id INVALID;

public:
    Entity() = default;
    Entity(EntityManager* manager, Entity::Id id);
    Entity(const Entity& other) = default;
    Entity& operator=(const Entity& other) = default;

    Id id() const;

    bool isValid() const;
    operator bool() const;
    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;
    bool operator<(const Entity& other) const;

    /**
     * Invalidate an entity but does not destroy it or its component.
     * To destroy an entity use destroy()
     */
    void invalidate();

    /**
     * Invalidate and destroy this entity and its component
     */
    void destroy();

    std::bitset<MAX_COMPONENTS> getComponentMask() const;

    template<typename C, typename... Args>
    ComponentHandle<C> assign(Args&&... args);

    /**
     * @return ComponentHandle<C> The new component handle
     */
    template<typename C, typename... Args>
    ComponentHandle<C> replace(Args&&... args);

    template<typename C>
    void remove();

    template<typename C>
    ComponentHandle<C> component();

    template<typename... Components>
    std::tuple<ComponentHandle<Components>...> components();

    template<typename C>
    bool hasComponent() const;

private:
    EntityManager* mManager;
    Entity::Id     mId = INVALID;
};

/**
 * Raised after the entity has been added to an EntityManager
 */
struct EntityCreatedEvent : public GameEvent<EntityCreatedEvent>
{
    explicit EntityCreatedEvent(Entity entity)
      : entity(entity)
    {
    }
    ~EntityCreatedEvent() = default;

    Entity entity;

#if FLUFFY_DEBUG
    virtual const String toString() const
    {
        return fmt::format("'EntityCreatedEvent' {{entityId:{}}}", entity.id().index());
    }
#endif
};

/**
 * Raised before the entity is being destroyed
 */
struct EntityDestroyedEvent : public GameEvent<EntityDestroyedEvent>
{
    explicit EntityDestroyedEvent(Entity entity)
      : entity(entity)
    {
    }
    ~EntityDestroyedEvent() = default;

    Entity entity;

#if FLUFFY_DEBUG
    virtual const String toString() const
    {
        return fmt::format("'EntityDestroyedEvent' {{entityId:{}}}", entity.id().index());
    }
#endif
};
}
