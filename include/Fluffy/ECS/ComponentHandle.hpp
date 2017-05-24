//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#ifndef FLUFFY_COMPONENTHANDLE_HPP
#define FLUFFY_COMPONENTHANDLE_HPP

#include <Fluffy/ECS/Entity.hpp>

namespace Fluffy {
namespace ECS {

class EntityManager;

template <typename C>
class ComponentHandle
{
public:
    ComponentHandle();

    bool isValid() const;
    operator bool() const;

    C* operator->();
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
}

#endif //FLUFFY_COMPONENTHANDLE_HPP
