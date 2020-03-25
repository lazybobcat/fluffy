#pragma once

#include <cassert>
#include <fluffy/ecs/component_handle.hpp>
#include <memory>

namespace Fluffy {

/**
 *  Base Component - do not use this, inherit from Component instead
 */
struct BaseComponent
{
public:
    typedef std::size_t Family;

public:
    virtual ~BaseComponent() = default;

    void operator delete(void* p) { fail(); }
    void operator delete[](void* p) { fail(); }

protected:
    static void fail();

    static Family mFamilyCounter;
};

/**
 * Must provide a default constructor
 *
 * Usage :
 *  struct Position : public Component<Position> {
 *      Position() : x(0), y(0) {}
 *
 *      float x, y;
 *  }
 */
template<typename Derived>
struct Component : public BaseComponent
{
public:
    typedef ComponentHandle<Derived>       Handle;
    typedef ComponentHandle<const Derived> ConstHandle;

#if FLUFFY_ENV_DEBUG
    virtual const std::string toString() const
    {
        return "'UnnamedComponent' {}";
    }
#endif

private:
    friend class EntityManager;

    static Family family()
    {
        static Family family = mFamilyCounter++;
        assert(family < MAX_COMPONENTS);

        return family;
    }
};

class BaseComponentHelper
{
public:
    virtual ~BaseComponentHelper()              = default;
    virtual void removeComponent(Entity entity) = 0;
};

template<typename C>
class ComponentHelper : public BaseComponentHelper
{
public:
    void removeComponent(Entity entity) override
    {
        entity.remove<C>();
    }
};

/**
 * Raised after the component has been added to an entity
 */
template<typename C>
struct ComponentAddedEvent : public Event<ComponentAddedEvent<C>>
{
    ComponentAddedEvent(Entity entity, ComponentHandle<C> component)
      : entity(entity)
      , component(component)
    {
    }
    ~ComponentAddedEvent() = default;

    Entity             entity;
    ComponentHandle<C> component;

#if FLUFFY_ENV_DEBUG
    virtual const std::string toString() const
    {
        return "'ComponentAddedEvent' {entityId:" + Fluffy::toString(entity.id().index()) + ", component=" + component.get()->toString() + "}";
    }
#endif
};

/**
 * Raised before the component is removed from an entity
 */
template<typename C>
struct ComponentRemovedEvent : public Event<ComponentRemovedEvent<C>>
{
    ComponentRemovedEvent(Entity entity, ComponentHandle<C> component)
      : entity(entity)
      , component(component)
    {
    }
    ~ComponentRemovedEvent() = default;

    Entity             entity;
    ComponentHandle<C> component;

#if FLUFFY_ENV_DEBUG
    virtual const std::string toString() const
    {
        return "'ComponentRemovedEvent' {entityId:" + Fluffy::toString(entity.id().index()) + ", component=" + component.get()->toString() + "}";
    }
#endif
};
}
