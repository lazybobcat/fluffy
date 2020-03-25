#pragma once

#include <fluffy/ecs/entity.hpp>

namespace Fluffy {

class EntityManager;

template<typename C>
class ComponentHandle
{
public:
    ComponentHandle();

    bool isValid() const;
    operator bool() const;

    C*       operator->();
    const C* operator->() const;

    C*       get();
    const C* get() const;

    /**
     * Remove the component from the entity and destroy it
     */
    void remove();

    Entity getEntity();

    bool operator==(const ComponentHandle<C>& other) const;

    bool operator!=(const ComponentHandle<C>& other) const;

private:
    friend class EntityManager;

    ComponentHandle(EntityManager* manager, Entity::Id id);

private:
    EntityManager* mManager;
    Entity::Id     mId;
};
}
