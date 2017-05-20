//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#ifndef FLUFFY_ENTITYMANAGER_HPP
#define FLUFFY_ENTITYMANAGER_HPP

#include <Fluffy/ECS/Entity.hpp>
#include <Fluffy/ECS/View/EntityComponentView.hpp>
#include <Fluffy/Lua/Bindable.hpp>
#include <stack>
#include <typeindex>
#include <vector>

namespace Fluffy {
namespace ECS {

class EntityManager : public Lua::Bindable
{
public:
    EntityManager();

    Entity::WeakPtr createEntity();
    void removeEntity(Entity::WeakPtr entity);
    Entity::WeakPtr entityByIndex(std::size_t index) const;
    Entity::WeakPtr entity(Entity::Ref ref) const;
    template <typename... Types>
    EntityComponentView<Types...> each();

    void        removeAllEntities();
    void        clear();
    std::size_t size() const;

    virtual void bind(sel::State& state);

private:
    Entity::Ref             mNextRef;
    std::stack<Entity::Ref> mFreeRefs;

    std::vector<Entity::Ptr> mEntities;
    std::map<Entity::Ref, Entity::Ptr> mEntitiesByRef;
};

#include <Fluffy/ECS/EntityManager.inl>
#include <Fluffy/ECS/View/EntityComponentView.inl>
}
}

#endif //FLUFFY_ENTITYMANAGER_HPP
